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
#include <iostream>

#include <boost/url.hpp>

namespace mini_crypto
{

node::node(const node_create_info& create_info):
	resolver(io),
	port(create_info.port),
	pairs(create_info.pairs.begin(), create_info.pairs.end())
{}

int node::run()
{
	tcp_server server(io, port);

	for(const auto& pair: pairs)
	{
		std::cout << pair << '\n';

		auto url = boost::urls::parse_uri(pair);

		if(!url)
			continue;

		for(const auto& endpoint: resolver.resolve(url->host(), url->port()))
		{
			std::cout << '\t' << endpoint.endpoint() << '\n';
		}

		// TODO: Connect to pair
	}

	#pragma omp parallel
	io.run();

	return EXIT_SUCCESS;
}

}
