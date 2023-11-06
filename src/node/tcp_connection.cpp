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

#include "node.hpp"
#include "tcp_connection.hpp"
#include "tcp_server.hpp"

#include <msgpack.hpp>

#include <iostream>
#include <sstream>

namespace mini_crypto
{

tcp_connection::tcp_connection(asio::io_context& io, tcp_server& server):
	io(io),
	server(server),
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

	asio::async_read_until(socket, buffer, EOF,
		[self](boost::system::error_code ec, std::size_t)
		{
			if(!ec || ec == asio::error::eof)
			{
				std::string msg(asio::buffer_cast<const char*>(self->buffer.data()), self->buffer.size());

				std::cout << msg << '\n';

				self->server.broadcast(msg);
			}
			else
				std::cerr << ec.message() << '\n';
		}
	);
}

void tcp_connection::write()
{
	std::string msg = "Hello world\n";

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

void tcp_connection::broadcast_write(const std::string& msg)
{
	auto self = shared_from_this();

	asio::async_write(
		socket,
		asio::buffer(msg),
		[self](boost::system::error_code ec, std::size_t)
		{
			if(ec)
				std::cerr << ec.message() << '\n';
		}
	);
}

void tcp_connection::start_connection()
{
	std::stringstream ss;

	ss << socket.remote_endpoint();

	started        = true;
	remote_address = ss.str();

	std::cerr << "Connection started with: " << remote_address << '\n';
}

void tcp_connection::start()
{
	start_connection();
	read();
}

void tcp_connection::start_broadcast(const std::string& msg)
{
	start_connection();
	broadcast_write(msg);
}

}
