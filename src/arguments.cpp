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

#include "arguments.hpp"

#include <cstdlib>
#include <getopt.h>
#include <iostream>

namespace mini_crypto
{

void arguments::usage(int exit_code) const
{
	std::cout
		<< "Usage: " << argv[0] << " [OPTION]... PAIRS...\n"
		<< "\t-h, --help      Show this help.\n"
		<< "\t-p, --port=PORT Listening port.\n"
	;

	exit(exit_code);
}

arguments::arguments(int argc, char** argv):
	argc(argc),
	argv(argv)
{}

void arguments::parse()
{
	if(argc < 2)
		usage(EXIT_FAILURE);

	int c;

	static const char shortopts[] = "hp:";
	static const option options[] =
	{
		{"help",  no_argument,       nullptr, 'h'},
		{"port",  required_argument, nullptr, 'p'},
		{nullptr, 0,                 nullptr, 0},
	};

	while((c = getopt_long(argc, argv, shortopts, options, nullptr)) != -1)
	{
		switch(c)
		{
			case 'h':
				usage(EXIT_SUCCESS);
				break;

			case 'p':
				port = atoi(optarg);
				break;

			case '?':
			default:
				usage(EXIT_FAILURE);
		}
	}

	for(int i = optind; i < argc; i++)
	{
		pairs.emplace_back(argv[i]);
	}

	if(pairs.empty())
	{
		std::cerr << "Missing pairs\n";
		usage(EXIT_FAILURE);
	}
}

node_create_info arguments::get_node_create_info() const
{
	return {
		.port  = port,
		.pairs = pairs,
	};
}

}
