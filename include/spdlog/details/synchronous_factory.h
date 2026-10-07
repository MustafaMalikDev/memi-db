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

#include "registry.h"

namespace spdlog
{

// Default logger factory-  creates synchronous loggers
class logger;

struct synchronous_factory {
	template <typename Sink, typename... SinkArgs>
	static std::shared_ptr<spdlog::logger> create(std::string logger_name,
						      SinkArgs&&... args)
	{
		auto sink =
			std::make_shared<Sink>(std::forward<SinkArgs>(args)...);
		auto new_logger = std::make_shared<spdlog::logger>(
			std::move(logger_name), std::move(sink));
		details::registry::instance().initialize_logger(new_logger);
		return new_logger;
	}
};
} // namespace spdlog
