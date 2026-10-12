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

#include "cli/flag.h"
#include "cli/port.h"
#include "net/socket.h"
#include "query/msql.h"
#include <iostream>

using namespace memi;

void signal_handle(int signal);

int main(int argc, char* argv[])
{
	signal(SIGTRAP, signal_handle);
	signal(SIGINT, signal_handle);
	signal(SIGKILL, signal_handle);

	msql_query query("GET key_name");
	query.execute();

	port& port = port::instance(argc, argv);

	/* clang-format off */
    /* https://patorjk.com/software/taag/#p=display&f=RubiFont&t=memi-db&x=none&v=4&h=4&w=80&we=false */
    std::cout << "\n";
	std::cout << "▗▖  ▗▖▗▄▄▄▖▗▖  ▗▖▗▄▄▄▖▗▄▄▄ ▗▄▄▖\t\t memi-db" << '\n';
	std::cout << "▐▛▚▞▜▌▐▌   ▐▛▚▞▜▌  █  ▐▌  █▐▌ ▐▌\t Research In-Memory Database" << '\n';
	std::cout << "▐▌  ▐▌▐▛▀▀▘▐▌  ▐▌  █  ▐▌  █▐▛▀▚▖\t Port: " << port.get_port() << '\n';
	std::cout << "▐▌  ▐▌▐▙▄▄▖▐▌  ▐▌▗▄█▄▖▐▙▄▄▀▐▙▄▞\t\t PID: " << getpid() << '\n';
    std::cout << "\n";
	/* clang-format on */

	/* have to use memi::socket otherwise it will get confused with C++ socket lol */
	memi::socket sock(port.get_port(), 1024, 8);
	sock.start();
}
