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

#include "handle.hpp"
#include "pairs.hpp"

#include <functional>
#include <unordered_map>

namespace mini_crypto::message
{

handle::handle(const char* data, size_t size)
{
	using namespace rapidjson;

	Document document;
	document.Parse(data, size);

	load(document);
}

handle::handle(const boost::asio::streambuf& sb):
	handle(boost::asio::buffer_cast<const char*>(sb.data()), sb.size())
{
}

void handle::dump(rapidjson::Writer<rapidjson::StringBuffer>& writer) const
{
	writer.StartObject();

	writer.Key("name");
	writer.String(name);

	writer.Key("data");
	data->dump(writer);

	writer.EndObject();
}

bool handle::load(const rapidjson::Value& value)
{
	if(!value.IsObject())
		return false;

	if(auto name = value.FindMember("name"); name != value.MemberEnd() && name->value.IsString())
	{
		this->name = name->value.GetString();
	}

	if(auto name = value.FindMember("data"); name != value.MemberEnd() && name->value.IsObject())
	{
		if(!(data = name2ptr(name->value.GetString())))
			return false;

		data->load(name->value);
	}

	return true;
}

std::unique_ptr<base> handle::name2ptr(const std::string& name)
{
	static const std::unordered_map<std::string, std::function<std::unique_ptr<base>()>> m =
	{
		{pairs::name, [](){return std::make_unique<pairs>();}}
	};

	auto it = m.find(name);

	if(it != m.end())
		return it->second();

	return nullptr;
}

}
