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

#include <atomic>
#include <utility>
// null, no cost dummy "mutex" and dummy "atomic" int

namespace spdlog
{
namespace details
{
struct null_mutex {
	void lock() const
	{
	}
	void unlock() const
	{
	}
};

struct null_atomic_int {
	int value;
	null_atomic_int() = default;

	explicit null_atomic_int(int new_value)
		: value(new_value)
	{
	}

	int load(std::memory_order = std::memory_order_relaxed) const
	{
		return value;
	}

	void store(int new_value, std::memory_order = std::memory_order_relaxed)
	{
		value = new_value;
	}

	int exchange(int new_value,
		     std::memory_order = std::memory_order_relaxed)
	{
		std::swap(new_value, value);
		return new_value; // return value before the call
	}
};

} // namespace details
} // namespace spdlog
