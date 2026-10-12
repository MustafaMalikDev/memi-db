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

#include "util/stob.h"
#include <sstream>

namespace memi
{

bool stob(const std::string& str)
{
	MEMI_RETURN_QUICK_IF(str.empty(), false)

	bool flag;
	std::istringstream(str) >> std::boolalpha >> flag;

	return flag;
}

bool stob(const std::string_view& str)
{
	return stob(std::string(str));
}

}
