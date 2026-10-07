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
#	include <spdlog/details/log_msg.h>
#endif

#include <spdlog/details/os.h>

namespace spdlog
{
namespace details
{

SPDLOG_INLINE
log_msg::log_msg(spdlog::log_clock::time_point log_time, spdlog::source_loc loc,
		 string_view_t a_logger_name, spdlog::level::level_enum lvl,
		 spdlog::string_view_t msg)
	: logger_name(a_logger_name)
	, level(lvl)
	, time(log_time)
#ifndef SPDLOG_NO_THREAD_ID
	, thread_id(os::thread_id())
#endif
	, source(loc)
	, payload(msg)
{
}

SPDLOG_INLINE
log_msg::log_msg(spdlog::source_loc loc, string_view_t a_logger_name,
		 spdlog::level::level_enum lvl, spdlog::string_view_t msg)
	: log_msg(os::now(), loc, a_logger_name, lvl, msg)
{
}

SPDLOG_INLINE log_msg::log_msg(string_view_t a_logger_name,
			       spdlog::level::level_enum lvl,
			       spdlog::string_view_t msg)
	: log_msg(os::now(), source_loc{}, a_logger_name, lvl, msg)
{
}

} // namespace details
} // namespace spdlog
