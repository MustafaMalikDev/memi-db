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

#include <spdlog/details/null_mutex.h>
#include <spdlog/details/synchronous_factory.h>
#include <spdlog/sinks/base_sink.h>

#include <mutex>

namespace spdlog
{
namespace sinks
{

template <typename Mutex> class null_sink : public base_sink<Mutex> {
protected:
	void sink_it_(const details::log_msg&) override
	{
	}
	void flush_() override
	{
	}
};

using null_sink_mt = null_sink<details::null_mutex>;
using null_sink_st = null_sink<details::null_mutex>;

} // namespace sinks

template <typename Factory = spdlog::synchronous_factory>
inline std::shared_ptr<logger> null_logger_mt(const std::string& logger_name)
{
	auto null_logger =
		Factory::template create<sinks::null_sink_mt>(logger_name);
	null_logger->set_level(level::off);
	return null_logger;
}

template <typename Factory = spdlog::synchronous_factory>
inline std::shared_ptr<logger> null_logger_st(const std::string& logger_name)
{
	auto null_logger =
		Factory::template create<sinks::null_sink_st>(logger_name);
	null_logger->set_level(level::off);
	return null_logger;
}

} // namespace spdlog
