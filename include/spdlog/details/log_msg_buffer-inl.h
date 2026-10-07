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
#	include <spdlog/details/log_msg_buffer.h>
#endif

namespace spdlog
{
namespace details
{

SPDLOG_INLINE log_msg_buffer::log_msg_buffer(const log_msg& orig_msg)
	: log_msg{ orig_msg }
{
	buffer.append(logger_name.begin(), logger_name.end());
	buffer.append(payload.begin(), payload.end());
	update_string_views();
}

SPDLOG_INLINE log_msg_buffer::log_msg_buffer(const log_msg_buffer& other)
	: log_msg{ other }
{
	buffer.append(logger_name.begin(), logger_name.end());
	buffer.append(payload.begin(), payload.end());
	update_string_views();
}

SPDLOG_INLINE
log_msg_buffer::log_msg_buffer(log_msg_buffer&& other) SPDLOG_NOEXCEPT
	: log_msg{ other },
	  buffer{ std::move(other.buffer) }
{
	update_string_views();
}

SPDLOG_INLINE log_msg_buffer&
log_msg_buffer::operator=(const log_msg_buffer& other)
{
	log_msg::operator=(other);
	buffer.clear();
	buffer.append(other.buffer.data(),
		      other.buffer.data() + other.buffer.size());
	update_string_views();
	return *this;
}

SPDLOG_INLINE log_msg_buffer&
log_msg_buffer::operator=(log_msg_buffer&& other) SPDLOG_NOEXCEPT
{
	log_msg::operator=(other);
	buffer = std::move(other.buffer);
	update_string_views();
	return *this;
}

SPDLOG_INLINE void log_msg_buffer::update_string_views()
{
	logger_name = string_view_t{ buffer.data(), logger_name.size() };
	payload = string_view_t{ buffer.data() + logger_name.size(),
				 payload.size() };
}

} // namespace details
} // namespace spdlog
