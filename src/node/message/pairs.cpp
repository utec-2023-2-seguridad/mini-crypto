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

	writer.Key("urls");
	writer.StartArray();

	for(const auto& url: urls)
	{
		writer.String(url);
	}

	writer.EndArray();

	writer.EndObject();
}

bool pairs::load(const rapidjson::Value& value)
{
	if(!value.IsObject())
		return false;

	if(auto urls = value.FindMember("urls"); urls != value.MemberEnd() && urls->value.IsArray())
	{
		for(const auto& url: urls->value.GetArray())
		{
			if(url.IsString())
			{
				this->urls.emplace_back(url.GetString());
			}
		}
	}

	return true;
}

}
