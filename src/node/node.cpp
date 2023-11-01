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
#include <cstring>
#include <iostream>
#include <memory>

namespace mini_crypto
{

node::node(const node_create_info& create_info):
	resolver(io),
	port(create_info.port)
{
	entt::sigh_helper{registry}
		.with<name_t>()
			.on_construct<&node::parse_pair_url>(*this)
	;

	for(const auto& pair: create_info.pairs)
	{
		entt::entity pair_e = registry.create();

		registry.emplace<name_t>(pair_e, pair);
	}
}

int node::run()
{
	tcp_server server(io, port, *this);

	io.run();

	return EXIT_SUCCESS;
}

void node::parse_pair_url(entt::registry& registry, entt::entity entity)
{
	auto url = parse_url(registry.get<name_t>(entity));

	if(!url)
		return;

	boost::system::error_code ec;
	auto endpoints = resolver.resolve(url->host, url->port, ec);

	if(ec)
	{
		std::cerr << ec.message() << '\n';
		return;
	}

	registry.emplace<endpoints_t>(entity, std::move(endpoints));
}

std::optional<node::url> node::parse_url(const std::string& url_string)
{
	char* saveptr;
	char* str_dup = strdup(url_string.c_str());

	url new_url;
	int i = 0;

	for(char* token = strtok_r(str_dup, ":", &saveptr); token != nullptr; token = strtok_r(nullptr, ":", &saveptr))
	{
		if(i == 0)
			new_url.host = token;
		else if(i == 1)
			new_url.port = token;

		i++;
	}

	free(str_dup);

	if(i == 2)
		return new_url;
	else
		return {};
}

entt::registry& node::get_registry()
{
	return registry;
}

}
