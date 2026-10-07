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
#include <string>

namespace spdlog
{

// callbacks type
typedef std::function<void(const details::log_msg& msg)> custom_log_callback;

namespace sinks
{
/*
 * Trivial callback sink, gets a callback function and calls it on each log
 */
template <typename Mutex> class callback_sink final : public base_sink<Mutex> {
public:
	explicit callback_sink(const custom_log_callback& callback)
		: callback_{ callback }
	{
	}

protected:
	void sink_it_(const details::log_msg& msg) override
	{
		callback_(msg);
	}
	void flush_() override {};

private:
	custom_log_callback callback_;
};

using callback_sink_mt = callback_sink<std::mutex>;
using callback_sink_st = callback_sink<details::null_mutex>;

} // namespace sinks

//
// factory functions
//
template <typename Factory = spdlog::synchronous_factory>
inline std::shared_ptr<logger>
callback_logger_mt(const std::string& logger_name,
		   const custom_log_callback& callback)
{
	return Factory::template create<sinks::callback_sink_mt>(logger_name,
								 callback);
}

template <typename Factory = spdlog::synchronous_factory>
inline std::shared_ptr<logger>
callback_logger_st(const std::string& logger_name,
		   const custom_log_callback& callback)
{
	return Factory::template create<sinks::callback_sink_st>(logger_name,
								 callback);
}

} // namespace spdlog
