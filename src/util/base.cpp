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

#include "util/base.h"

namespace memi
{
bool is_base2(const std::string& str)
{
	MEMI_RETURN_QUICK_IF(str.empty(), false)

	bool is_valid = false;

	/* https://cplusplus.com/forum/general/100956/ */
	for (int i = 0; i < str.size(); ++i) {
		if (str[i] - '0' >= 2) {
			is_valid = false;
			break;
		}
	}

	return is_valid;
}

bool is_base2(const std::string_view& str)
{
	return is_base2(std::string(str));
}

bool is_base2(const uint16_t num)
{
	return num % 2 == 0;
}

}
