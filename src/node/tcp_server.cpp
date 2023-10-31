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

#include "tcp_server.hpp"

#include <cstdlib>
#include <iostream>

namespace mini_crypto
{

tcp_server::tcp_server(asio::io_context& io, int port):
	io(io),
	acceptor(io, tcp::endpoint(tcp::v4(), port))
{
	// TODO: Start listening and sending requests to the p2p network
	std::cout << "Hello\n";
}

}
