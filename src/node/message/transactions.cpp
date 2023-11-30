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

#include "transactions.hpp"

namespace mini_crypto::message
{

void transactions::dump(rapidjson::Writer<rapidjson::StringBuffer>& writer) const
{
	writer.StartObject();

	writer.Key("txs");
	writer.StartArray();

	for(const auto& tx: txs)
	{
		// TODO: string -> transaction
		writer.String(tx);
	}

	writer.EndArray();

	writer.Key("jumps_left");
	writer.Int(jumps_left);

	writer.EndObject();
}

bool transactions::load(const rapidjson::Value& value)
{
	if(!value.IsObject())
		return false;

	if(auto txs = value.FindMember("txs"); txs != value.MemberEnd() && txs->value.IsArray())
	{
		for(const auto& tx: txs->value.GetArray())
		{
			if(tx.IsString())
			{
				this->txs.emplace_back(tx.GetString());
			}
		}
	}

	if(auto jumps_left = value.FindMember("jumps_left"); jumps_left != value.MemberEnd() && jumps_left->value.IsInt())
	{
		this->jumps_left = jumps_left->value.GetInt();
	}

	return true;
}

}
