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

#include <cstdlib>
#include <iostream>

namespace mini_crypto
{

tcp_server::tcp_server(asio::io_context& io, int port, node& root):
	io(io),
	root(root),
	acceptor(io, tcp::endpoint(tcp::v4(), port))
{
	start_listening();

	auto view = root.get_registry().view<node::name_t, node::endpoints_t>();

	for(auto [_, name, endpoints]: view.each())
	{
		connect(name, endpoints);
	}

}

void tcp_server::start_listening()
{
	auto connection = tcp_connection::make(io);

	acceptor.async_accept(
		connection->get_socket(),
		[this, connection](boost::system::error_code ec)
		{
			if(!ec)
				connection->start();
			else
				std::cerr << ec.message() << '\n';

			start_listening();
		}
	);
}

void tcp_server::connect(const std::string& name, const tcp::resolver::results_type& endpoints)
{
	auto connection = tcp_connection::make(io);

	asio::async_connect(
		connection->get_socket(),
		endpoints,
		[connection, name](boost::system::error_code ec, const tcp::endpoint&)
		{
			if(!ec)
				connection->start();
			else
				std::cerr << ec.message() << ": " << name << '\n';
		}
	);
}

}
