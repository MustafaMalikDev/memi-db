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

#include "net/socket.h"
#include "spdlog/spdlog.h"
#include "cli/port.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <memory>
#include <vector>
#include <iostream>

static std::vector<int> g_sockfds;
static bool             g_signal_invoked = false;
extern void             signal_handle(int signal);

void signal_handle(int signal)
{
	g_signal_invoked = true;

	if (g_sockfds.empty()) {
		return;
	}

	for (int sockfd : g_sockfds) {
		if (sockfd != -1) {
			close(sockfd);
		}
	}
}

namespace memi
{

socket::socket(uint16_t port, uint16_t maxbuf, uint8_t max_queue)
        : m_port(port)
        , m_maxbuf(maxbuf)
        , m_max_queue(max_queue)
{
	memset(&m_server_addr, 0, sizeof(m_server_addr));
}

socket::~socket()
{
	cleanup();
}

bool socket::is_port_available()
{
	struct sockaddr_in server_addr;
	int                sock_fd;

	if ((sock_fd = ::socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		return false;
	}

	memset(&server_addr, 0, sizeof(server_addr));

	server_addr.sin_family      = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port        = htons(m_port);

	if (bind(sock_fd, (struct sockaddr*) &server_addr,
	         sizeof(server_addr)) == -1) {
		close(sock_fd);
		return false;
	}

	close(sock_fd);
	return true;
}

void socket::start()
{
	if (m_port == MEMIDB_DEFAULT_PORT) {
		int  max_limit     = std::numeric_limits<uint16_t>::max();
		int  max_tries     = 4;
		int  current_tries = 0;
		bool is_avail      = false;

		do {
			is_avail = is_port_available();

			if (m_port == max_limit || current_tries == max_tries) {
				break;
			}

			if (!is_avail) {
				m_port++;
			}

			current_tries++;
		} while (!is_avail);

		if (!is_avail) {
			spdlog::error(
			        "could not start server. port {} is busy and all port options are exhausted.",
			        m_port);
			std::exit(EXIT_FAILURE);
		}
	}

	if ((m_sockfd = ::socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		spdlog::error("could not create socket. abort.");
		std::exit(EXIT_FAILURE);
	}

	g_sockfds.push_back(m_sockfd);

	m_server_addr.sin_family      = AF_INET;
	m_server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_server_addr.sin_port        = htons(m_port);

	if ((m_bindfd = bind(m_sockfd, (const sockaddr*) &m_server_addr,
	                     sizeof(m_server_addr))) == -1) {
		spdlog::error("could not bind socket. abort.");
		close(m_sockfd);
		std::exit(EXIT_FAILURE);
	}

	if (listen(m_sockfd, m_max_queue) == -1) {
		spdlog::error("could not listen on socket. abort.");
		close(m_sockfd);
		std::exit(EXIT_FAILURE);
	}

	m_running      = true;
	char* readbuf  = new char[m_maxbuf];
	int   clientfd = -1;
	int   rv       = -1;

	memset(readbuf, 0, m_maxbuf);

	while (m_running) {
		if (g_signal_invoked) {
			m_running = false;
			break;
		}

		if ((clientfd = accept(m_sockfd, (struct sockaddr*) nullptr,
		                       nullptr)) == -1) {
			continue;
		}

		if ((rv = read(clientfd, readbuf, sizeof(readbuf))) == -1) {
			close(clientfd);
			continue;
		}

		close(clientfd);
		readbuf[0] = 0;
	}

	if (readbuf) {
		delete[] readbuf;
	}
}

void socket::cleanup()
{
	if (m_sockfd > -1) {
		spdlog::info("closing socket file descriptor");

		close(m_sockfd);
		memset(&m_server_addr, 0, sizeof(m_server_addr));

		g_sockfds.erase(
		        std::remove_if(g_sockfds.begin(), g_sockfds.end(),
			               [&](int sockfd) -> bool {
			                       return sockfd == m_sockfd;
		                       }));

		m_sockfd  = -1;
		m_bindfd  = -1;
		m_running = false;

		spdlog::info("memi-db ready to stop. bye bye :-)");
	}
}

}
