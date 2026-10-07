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

#include "arg2vec.h"
#include "flag.h"
#include "util/stos.h"
#include "spdlog/spdlog.h"

#define MEMIDB_DEFAULT_PORT 6721

namespace memi
{

class port final {
private:
	port() = default;
	~port() = default;

	MEMI_NO_COPY_MOVE(port)

private:
	bool is_available() const;

public:
	MEMI_DECLARE_SINGLETON(port, int argc, char* argv[])
	{
		static port p;
		p.m_args = args2vec(argc, argv);
		std::string_view port_str = extract_flag("port", p.m_args);

		if (!port_str.empty()) {
			int16_t np;

			if ((np = stos(port_str)) > 0) {
				p.m_port = np;
				spdlog::info(
					"custom port requested. set port to: {}",
					np);
			} else {
				spdlog::warn(
					"could not set custom port. defaulting to: {}",
					MEMIDB_DEFAULT_PORT);
			}
		}

		return p;
	}

private:
	uint16_t m_port{ MEMIDB_DEFAULT_PORT };
	std::vector<std::string_view> m_args{};
};

}

#endif /* _MEMIDB_CLI_PORT_H_ */
