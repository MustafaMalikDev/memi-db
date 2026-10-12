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

#ifndef _MEMIDB_NET_SOCKET_H_
#define _MEMIDB_NET_SOCKET_H_

#include "config.h"
#include <netinet/in.h>

#define MEMI_DEFAULT_SOCK_BUF 1024
#define MEMI_DEFAULT_SOCK_QUEUE 8

namespace memi
{

class socket final {
public:
	socket(uint16_t port, uint16_t maxbuf, uint8_t max_queue);
	~socket();

	MEMI_NO_COPY_MOVE(socket)

public:
	MEMI_FORCE_USE bool is_port_available();
	void                start();
	void                cleanup();

private:
	struct sockaddr_in m_server_addr;

	int      m_sockfd{ -1 };
	int      m_bindfd{ -1 };
	uint16_t m_port{ 0 };
	uint16_t m_maxbuf{ MEMI_DEFAULT_SOCK_BUF };
	uint8_t  m_max_queue{ MEMI_DEFAULT_SOCK_QUEUE };
	bool     m_running{ false };
};

}

#endif /* _MEMIDB_NET_SOCKET_H_ */
