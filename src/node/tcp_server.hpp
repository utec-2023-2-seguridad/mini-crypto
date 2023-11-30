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

#include "message.hpp"

#include <boost/asio.hpp>

#include <string>
#include <unordered_map>

namespace mini_crypto
{

class node;
class tcp_connection;

namespace asio = boost::asio;

class tcp_server
{
private:
	using tcp           = asio::ip::tcp;
	using handle_func_t = void(tcp_server::*)(const tcp_connection&, const message::base&);
	using handler_map_t = std::unordered_map<std::string, handle_func_t>;

	asio::io_context& io;
	node&             root;

	tcp::acceptor    acceptor;
	asio::signal_set signals;

	static const handler_map_t handler_map;

	entt::registry& get_registry();

	template <typename T>
	message::handle& make_message(entt::entity id, T&& message)
	{
		return get_registry().emplace<message::handle>(id, T::name, std::make_unique<T>(message));
	}

	void start_listening();
	void stop(boost::system::error_code ec, int signal);
	void handle(entt::entity message_id, const tcp_connection& connection);

	void handle_pairs(const tcp_connection& connection, const message::pairs& pairs);
	void handle_transactions(const tcp_connection& connection, const message::transactions& transactions);

public:
	tcp_server(asio::io_context& io, int port, node& root);

	void connect(const std::string& name, const tcp::resolver::results_type& endpoints, entt::entity message_id);
	void broadcast(entt::entity message_id);

	friend class tcp_connection;
};

}
