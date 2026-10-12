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

#include "cli/port.h"
#include "net/socket.h"

namespace memi
{

bool port::is_available() const
{
	return socket(m_port, MEMI_DEFAULT_SOCK_BUF, MEMI_DEFAULT_SOCK_QUEUE)
	        .is_port_available();
}

MEMI_DEFINE_SINGLETON(port, int argc, char* argv[])
{
	static port p;
	p.m_args                  = args2vec(argc, argv);
	std::string_view port_str = extract_flag("port", p.m_args);

	if (!port_str.empty()) {
		int16_t np;

		if ((np = stos(port_str)) > 0) {
			p.m_port = np;

			if (p.is_available()) {
				spdlog::info("successfully assigned port: {}",
				             np);
			} else {
				p.m_port = MEMIDB_DEFAULT_PORT;
				spdlog::warn(
				        "could not assign port: {}, defaulting to: {}",
				        np, p.m_port);
			}
		}
	}

	return p;
}

}
