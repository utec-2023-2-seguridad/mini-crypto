// Toy blockchain
// Copyright © 2023 Otreblan
//
// mini-crypto is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// mini-crypto is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with mini-crypto.  If not, see <http://www.gnu.org/licenses/>.

#include "tcp_connection.hpp"

#include "omp.h"

#include <iostream>
#include <sstream>

namespace mini_crypto
{

tcp_connection::tcp_connection(asio::io_context& io):
	io(io),
	socket(io)
{};

tcp_connection::~tcp_connection()
{
	if(started)
		std::cerr << "Connection ended with: " << remote_address << '\n';
}

tcp_connection::tcp::socket& tcp_connection::get_socket()
{
	return socket;
}

void tcp_connection::read()
{
	auto self = shared_from_this();

	socket.async_read_some(
		asio::buffer(data),
		[self](boost::system::error_code ec, std::size_t)
		{
			if(!ec)
				self->write();
			else
				std::cerr << ec.message() << '\n';
		}
	);
}

void tcp_connection::write()
{
	std::string msg = "Hello world from " + std::to_string(omp_get_thread_num()) + "\n";

	auto self = shared_from_this();

	asio::async_write(
		socket,
		asio::buffer(msg),
		[self](boost::system::error_code ec, std::size_t)
		{
			if(!ec)
				self->read();
			else
				std::cerr << ec.message() << '\n';
		}
	);
}

void tcp_connection::start()
{
	std::stringstream ss;

	ss << socket.remote_endpoint();

	started        = true;
	remote_address = ss.str();

	std::cerr << "Connection started with: " << remote_address << '\n';

	read();
}

}
