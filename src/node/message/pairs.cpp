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

#include "pairs.hpp"

namespace mini_crypto::message
{

void pairs::dump(rapidjson::Writer<rapidjson::StringBuffer>& writer) const
{
	writer.StartObject();

	// TODO

	writer.EndObject();
}

bool pairs::load(const rapidjson::Value& value)
{
	if(!value.IsObject())
		return false;

	if(auto name = value.FindMember("urls"); name != value.MemberEnd() && name->value.IsString())
	{
		// TODO
	}

	return true;
}

}
