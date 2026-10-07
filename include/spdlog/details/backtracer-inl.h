/**
 * This file is part of the memi-db distribution (https://github.com/MustafaMalikDev/memi-db)
 * Copyright (c) 2026 Mustafa Malik.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

// Copyright(c) 2015-present, Gabi Melman & spdlog contributors.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)

#pragma once

#ifndef SPDLOG_HEADER_ONLY
#	include <spdlog/details/backtracer.h>
#endif
namespace spdlog
{
namespace details
{
SPDLOG_INLINE backtracer::backtracer(const backtracer& other)
{
	std::lock_guard<std::mutex> lock(other.mutex_);
	enabled_ = other.enabled();
	messages_ = other.messages_;
}

SPDLOG_INLINE backtracer::backtracer(backtracer&& other) SPDLOG_NOEXCEPT
{
	std::lock_guard<std::mutex> lock(other.mutex_);
	enabled_ = other.enabled();
	messages_ = std::move(other.messages_);
}

SPDLOG_INLINE backtracer& backtracer::operator=(backtracer other)
{
	std::lock_guard<std::mutex> lock(mutex_);
	enabled_ = other.enabled();
	messages_ = std::move(other.messages_);
	return *this;
}

SPDLOG_INLINE void backtracer::enable(size_t size)
{
	std::lock_guard<std::mutex> lock{ mutex_ };
	enabled_.store(true, std::memory_order_relaxed);
	messages_ = circular_q<log_msg_buffer>{ size };
}

SPDLOG_INLINE void backtracer::disable()
{
	std::lock_guard<std::mutex> lock{ mutex_ };
	enabled_.store(false, std::memory_order_relaxed);
}

SPDLOG_INLINE bool backtracer::enabled() const
{
	return enabled_.load(std::memory_order_relaxed);
}

SPDLOG_INLINE void backtracer::push_back(const log_msg& msg)
{
	std::lock_guard<std::mutex> lock{ mutex_ };
	messages_.push_back(log_msg_buffer{ msg });
}

SPDLOG_INLINE bool backtracer::empty() const
{
	std::lock_guard<std::mutex> lock{ mutex_ };
	return messages_.empty();
}

// pop all items in the q and apply the given fun on each of them.
SPDLOG_INLINE void
backtracer::foreach_pop(std::function<void(const details::log_msg&)> fun)
{
	std::lock_guard<std::mutex> lock{ mutex_ };
	while (!messages_.empty()) {
		auto& front_msg = messages_.front();
		fun(front_msg);
		messages_.pop_front();
	}
}
} // namespace details
} // namespace spdlog
