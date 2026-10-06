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

#ifndef _MEMIDB_CLI_PORT_H_
#define _MEMIDB_CLI_PORT_H_

#include "config.h"
#include "arg2vec.h"

#define MEMIDB_DEFAULT_PORT 6721

namespace memi
{

class port final {
private:
	port();
	~port() = default;

	MEMI_NO_COPY_MOVE(port)

public:
	MEMI_DECLARE_SINGLETON(port, int argc, char* argv[])
	{
		static port p;
		p.m_args = args2vec(argc, argv);

		return p;
	}

private:
	uint16_t m_port{ MEMIDB_DEFAULT_PORT };
	std::vector<std::string_view> m_args{};
};

}

#endif /* _MEMIDB_CLI_PORT_H_ */
