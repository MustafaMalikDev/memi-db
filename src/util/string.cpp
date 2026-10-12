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

#include "util/string.h"

namespace memi
{

std::vector<std::string> split(const std::string_view& delim, std::string str)
{
	MEMI_RETURN_QUICK_IF(str.empty(), {});

	std::vector<std::string> tokens;
	size_t                   pos = 0;
	std::string              token;

	while ((pos = str.find(delim)) != std::string::npos) {
		token = str.substr(0, pos);
		tokens.push_back(token);
		str.erase(0, pos + delim.length());
	}

	tokens.push_back(str);
	return tokens;
}

bool is_upper(const std::string_view& str)
{
	MEMI_RETURN_QUICK_IF(str.empty(), false)

	for (char ch : str) {
		if (!std::isupper(ch)) {
			return false;
		}
	}

	return true;
}

}
