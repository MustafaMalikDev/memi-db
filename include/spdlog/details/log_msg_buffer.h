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

#include <spdlog/details/log_msg.h>

namespace spdlog
{
namespace details
{

// Extend log_msg with internal buffer to store its payload.
// This is needed since log_msg holds string_views that points to stack data.

class SPDLOG_API log_msg_buffer : public log_msg {
	memory_buf_t buffer;
	void update_string_views();

public:
	log_msg_buffer() = default;
	explicit log_msg_buffer(const log_msg& orig_msg);
	log_msg_buffer(const log_msg_buffer& other);
	log_msg_buffer(log_msg_buffer&& other) SPDLOG_NOEXCEPT;
	log_msg_buffer& operator=(const log_msg_buffer& other);
	log_msg_buffer& operator=(log_msg_buffer&& other) SPDLOG_NOEXCEPT;
};

} // namespace details
} // namespace spdlog

#ifdef SPDLOG_HEADER_ONLY
#	include "log_msg_buffer-inl.h"
#endif
