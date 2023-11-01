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

namespace mini_crypto
{

tcp_connection::tcp_connection(asio::io_context& io):
	io(io),
	socket(io)
{};

tcp_connection::tcp::socket& tcp_connection::get_socket()
{
	return socket;
}

void tcp_connection::handle_write(std::size_t bytes_transfered)
{
	// TODO
}

void tcp_connection::start()
{
	std::string msg = "Hello world\n";

	auto self = shared_from_this();

	asio::async_write(
		socket,
		asio::buffer(msg),
		[self](boost::system::error_code ec, std::size_t bytes_transfered)
		{
			if(!ec)
				self->handle_write(bytes_transfered);
		}
	);
}

}
