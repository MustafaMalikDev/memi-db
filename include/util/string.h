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

#ifndef _MEMIDB_UTIL_STRING_H_
#define _MEMIDB_UTIL_STRING_H_

#include "config.h"
#include <string>
#include <vector>

namespace memi
{

std::vector<std::string> split(const std::string_view& delim, std::string str);

std::vector<std::string> split(const std::string_view& delim,
			       const std::string_view& str);

}

#endif /* _MEMIDB_UTIL_STRING_H_ */
