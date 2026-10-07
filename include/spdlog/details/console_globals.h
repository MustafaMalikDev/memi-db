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

#include <mutex>
#include <spdlog/details/null_mutex.h>

namespace spdlog
{
namespace details
{

struct console_mutex {
	using mutex_t = std::mutex;
	static mutex_t& mutex()
	{
		static mutex_t s_mutex;
		return s_mutex;
	}
};

struct console_nullmutex {
	using mutex_t = null_mutex;
	static mutex_t& mutex()
	{
		static mutex_t s_mutex;
		return s_mutex;
	}
};
} // namespace details
} // namespace spdlog
