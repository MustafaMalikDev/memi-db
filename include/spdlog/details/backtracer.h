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

#include <spdlog/details/circular_q.h>
#include <spdlog/details/log_msg_buffer.h>

#include <atomic>
#include <functional>
#include <mutex>

// Store log messages in circular buffer.
// Useful for storing debug data in case of error/warning happens.

namespace spdlog
{
namespace details
{
class SPDLOG_API backtracer {
	mutable std::mutex mutex_;
	std::atomic<bool> enabled_{ false };
	circular_q<log_msg_buffer> messages_;

public:
	backtracer() = default;
	backtracer(const backtracer& other);

	backtracer(backtracer&& other) SPDLOG_NOEXCEPT;
	backtracer& operator=(backtracer other);

	void enable(size_t size);
	void disable();
	bool enabled() const;
	void push_back(const log_msg& msg);
	bool empty() const;

	// pop all items in the q and apply the given fun on each of them.
	void foreach_pop(std::function<void(const details::log_msg&)> fun);
};

} // namespace details
} // namespace spdlog

#ifdef SPDLOG_HEADER_ONLY
#	include "backtracer-inl.h"
#endif
