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

#include "cli/flag.h"
#include <iostream>

namespace memi
{

std::string_view extract_flag(const std::string& flag,
			      const std::vector<std::string_view>& args)
{
	MEMI_RETURN_QUICK_IF(flag.empty(), {})
	MEMI_RETURN_QUICK_IF(args.empty(), {})

	for (size_t i = 0; i < args.size(); i++) {
		std::string arg(args[i]);
		size_t dash_pos = arg.find("--");

		if (dash_pos == std::string::npos) {
			continue;
		}

		arg.erase(dash_pos, 2);

		if (arg == flag) {
			for (size_t j = i + 1; j < args.size(); j++) {
				if (args[j].find("--") == std::string::npos) {
					return args[j];
				}
			}
		}
	}

	return {};
}

}
