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

#include "util/stos.h"
#include <iostream>

namespace memi
{

int16_t stos(const std::string str)
{
	MEMI_RETURN_QUICK_IF(str.empty(), 0)

	int conv = std::stoi(str);
	int min = std::numeric_limits<int16_t>::lowest();
	int max = std::numeric_limits<int16_t>::max();

	if (conv >= min && conv <= max) {
		return (int16_t)conv;
	}

	return 0;
}

int16_t stos(const std::string_view str)
{
	return stos(std::string(str));
}

}
