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

#pragma once

#include "node/node_create_info.hpp"

#include <string>
#include <vector>

namespace mini_crypto
{

class arguments
{
private:
	int    argc;
	char** argv;

	int                      port;
	std::vector<std::string> pairs;

	[[noreturn]]
	void usage(int exit_code) const;

public:
	arguments(int argc, char** argv);

	void parse();

	node_create_info get_node_create_info() const;
};

}
