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
#	include <spdlog/sinks/stdout_color_sinks.h>
#endif

#include <spdlog/common.h>
#include <spdlog/logger.h>

namespace spdlog
{

template <typename Factory>
SPDLOG_INLINE std::shared_ptr<logger>
stdout_color_mt(const std::string& logger_name, color_mode mode)
{
	return Factory::template create<sinks::stdout_color_sink_mt>(
		logger_name, mode);
}

template <typename Factory>
SPDLOG_INLINE std::shared_ptr<logger>
stdout_color_st(const std::string& logger_name, color_mode mode)
{
	return Factory::template create<sinks::stdout_color_sink_st>(
		logger_name, mode);
}

template <typename Factory>
SPDLOG_INLINE std::shared_ptr<logger>
stderr_color_mt(const std::string& logger_name, color_mode mode)
{
	return Factory::template create<sinks::stderr_color_sink_mt>(
		logger_name, mode);
}

template <typename Factory>
SPDLOG_INLINE std::shared_ptr<logger>
stderr_color_st(const std::string& logger_name, color_mode mode)
{
	return Factory::template create<sinks::stderr_color_sink_st>(
		logger_name, mode);
}
} // namespace spdlog
