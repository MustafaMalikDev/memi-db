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

#pragma once

#include <map>
#include <string>

#include <spdlog/common.h>

namespace spdlog
{
class SPDLOG_API mdc {
public:
	using mdc_map_t = std::map<std::string, std::string>;

	static void put(const std::string& key, const std::string& value)
	{
		get_context()[key] = value;
	}

	static std::string get(const std::string& key)
	{
		auto& context = get_context();
		auto it = context.find(key);
		if (it != context.end()) {
			return it->second;
		}
		return "";
	}

	static void remove(const std::string& key)
	{
		get_context().erase(key);
	}

	static void clear()
	{
		get_context().clear();
	}

	static mdc_map_t& get_context()
	{
		static thread_local mdc_map_t context;
		return context;
	}
};

} // namespace spdlog
