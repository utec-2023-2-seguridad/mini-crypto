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

#include <boost/asio.hpp>

namespace mini_crypto
{

namespace asio = boost::asio;

class tcp_connection: public std::enable_shared_from_this<tcp_connection>
{
private:
	using tcp = asio::ip::tcp;

	asio::io_context& io;
	tcp::socket       socket;

	tcp_connection(asio::io_context& io);

	void handle_write(std::size_t bytes_transfered);

public:
	tcp::socket& get_socket();

	void start();

	template <typename... Args>
	static std::shared_ptr<tcp_connection> make(Args&&... args)
	{
		return std::shared_ptr<tcp_connection>(new tcp_connection(std::forward<Args>(args)...));
	}
};

}
