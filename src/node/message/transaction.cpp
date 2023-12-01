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

#include "transaction.hpp"

namespace mini_crypto::message
{


void transaction::dump(rapidjson::Writer<rapidjson::StringBuffer>& writer) const
{
    writer.StartObject();

    writer.Key("sender");
    writer.String(sender.c_str());

    writer.Key("receiver");
    writer.String(receiver.c_str());

    writer.Key("amount");
    writer.Double(amount);

    writer.EndObject();
}

bool transaction::load(const rapidjson::Value& value)
{
    if (!value.IsObject())
        return false;

    if (auto sender = value.FindMember("sender"); sender != value.MemberEnd() && sender->value.IsString())
    {
        this->sender = sender->value.GetString();
    }

    if (auto receiver = value.FindMember("receiver"); receiver != value.MemberEnd() && receiver->value.IsString())
    {
        this->receiver = receiver->value.GetString();
    }

    if (auto amount = value.FindMember("amount"); amount != value.MemberEnd() && amount->value.IsNumber())
    {
        this->amount = amount->value.GetDouble();
    }

    return true;
}

}
