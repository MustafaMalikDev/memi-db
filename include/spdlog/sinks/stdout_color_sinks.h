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

#ifdef _WIN32
#	include <spdlog/sinks/wincolor_sink.h>
#else
#	include <spdlog/sinks/ansicolor_sink.h>
#endif

#include <spdlog/details/synchronous_factory.h>

namespace spdlog
{
namespace sinks
{
#ifdef _WIN32
using stdout_color_sink_mt = wincolor_stdout_sink_mt;
using stdout_color_sink_st = wincolor_stdout_sink_st;
using stderr_color_sink_mt = wincolor_stderr_sink_mt;
using stderr_color_sink_st = wincolor_stderr_sink_st;
#else
using stdout_color_sink_mt = ansicolor_stdout_sink_mt;
using stdout_color_sink_st = ansicolor_stdout_sink_st;
using stderr_color_sink_mt = ansicolor_stderr_sink_mt;
using stderr_color_sink_st = ansicolor_stderr_sink_st;
#endif
} // namespace sinks

template <typename Factory = spdlog::synchronous_factory>
std::shared_ptr<logger>
stdout_color_mt(const std::string& logger_name,
		color_mode mode = color_mode::automatic);

template <typename Factory = spdlog::synchronous_factory>
std::shared_ptr<logger>
stdout_color_st(const std::string& logger_name,
		color_mode mode = color_mode::automatic);

template <typename Factory = spdlog::synchronous_factory>
std::shared_ptr<logger>
stderr_color_mt(const std::string& logger_name,
		color_mode mode = color_mode::automatic);

template <typename Factory = spdlog::synchronous_factory>
std::shared_ptr<logger>
stderr_color_st(const std::string& logger_name,
		color_mode mode = color_mode::automatic);

} // namespace spdlog

#ifdef SPDLOG_HEADER_ONLY
#	include "stdout_color_sinks-inl.h"
#endif
