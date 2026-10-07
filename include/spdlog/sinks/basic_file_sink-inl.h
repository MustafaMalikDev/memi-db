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
#	include <spdlog/sinks/basic_file_sink.h>
#endif

#include <spdlog/common.h>
#include <spdlog/details/os.h>

namespace spdlog
{
namespace sinks
{

template <typename Mutex>
SPDLOG_INLINE basic_file_sink<Mutex>::basic_file_sink(
	const filename_t& filename, bool truncate,
	const file_event_handlers& event_handlers)
	: file_helper_{ event_handlers }
{
	file_helper_.open(filename, truncate);
}

template <typename Mutex>
SPDLOG_INLINE const filename_t& basic_file_sink<Mutex>::filename() const
{
	return file_helper_.filename();
}

template <typename Mutex>
SPDLOG_INLINE void basic_file_sink<Mutex>::sink_it_(const details::log_msg& msg)
{
	memory_buf_t formatted;
	base_sink<Mutex>::formatter_->format(msg, formatted);
	file_helper_.write(formatted);
}

template <typename Mutex> SPDLOG_INLINE void basic_file_sink<Mutex>::flush_()
{
	file_helper_.flush();
}

} // namespace sinks
} // namespace spdlog
