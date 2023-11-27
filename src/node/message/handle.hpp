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

#include <memory>
#include <string>

#include <boost/asio.hpp>

#include "base.hpp"

namespace mini_crypto::message
{

struct handle: public base
{
	std::string           name;
	std::unique_ptr<base> data;

	handle(const std::string& name, std::unique_ptr<base>&& data);
	handle(const char* data, size_t size);
	handle(const boost::asio::streambuf& sb);

	template<typename Type, typename... Args>
	static handle make(Args &&... args)
	{
		return {Type::name, std::make_unique<Type>(std::forward<Args>(args)...)};
	}

	virtual void dump(rapidjson::Writer<rapidjson::StringBuffer>& writer) const;
	virtual bool load(const rapidjson::Value& value);

	virtual ~handle() {};

private:
	static std::unique_ptr<base> name2ptr(const std::string& name);
};

}
