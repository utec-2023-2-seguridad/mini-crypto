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
#include "tcp_server.hpp"

#include <cstdlib>

namespace mini_crypto
{

node::node(const node_create_info& create_info):
	port(create_info.port)
{}

int node::run()
{
	tcp_server server(io, port);

	#pragma omp parallel
	io.run();

	return EXIT_SUCCESS;
}

}
