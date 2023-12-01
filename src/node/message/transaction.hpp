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

#include <string>
#include <vector>
#include <compare>

#include "base.hpp"

namespace mini_crypto::message
{

struct transaction: public base
{
    static constexpr const char* name = "transaction";

    // Atributos específicos del mensaje de transacción
    std::string sender;
    std::string receiver;
    double amount;

    // Métodos para serialización y deserialización
    void dump(rapidjson::Writer<rapidjson::StringBuffer>& writer) const;
    bool load(const rapidjson::Value& value);

	auto operator<=>(const transaction&) const = default;
};

}
