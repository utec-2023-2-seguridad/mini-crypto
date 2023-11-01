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

#include <array>
#include <memory>

#include <boost/asio.hpp>

namespace mini_crypto
{

class tcp_server;

namespace asio = boost::asio;

class tcp_connection: public std::enable_shared_from_this<tcp_connection>
{
private:
	using tcp = asio::ip::tcp;

	asio::io_context& io;
	tcp_server&       server;
	tcp::socket       socket;

	bool        started = false;
	std::string remote_address;

	std::array<char, PIPE_BUF> data;

	tcp_connection(asio::io_context& io, tcp_server& root);

	void read();
	void write();

	void broadcast_write(const std::string& msg);

	void start_connection();

public:
	~tcp_connection();

	tcp::socket& get_socket();

	void start();
	void start_broadcast(const std::string& msg);

	template <typename... Args>
	static std::shared_ptr<tcp_connection> make(Args&&... args)
	{
		return std::shared_ptr<tcp_connection>(new tcp_connection(std::forward<Args>(args)...));
	}
};

}
