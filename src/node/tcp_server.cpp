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

#include "node.hpp"
#include "tcp_connection.hpp"
#include "tcp_server.hpp"

#include <cstdlib>
#include <iostream>
#include <set>

namespace mini_crypto
{

const tcp_server::handler_map_t tcp_server::handler_map =
{
	{message::pairs::name, reinterpret_cast<tcp_server::handle_func_t>(&tcp_server::handle_pairs)},
	{message::transactions::name, reinterpret_cast<tcp_server::handle_func_t>(&tcp_server::handle_transactions)},
	// TODO: Add more handlers
};

entt::registry& tcp_server::get_registry()
{
	return root.get_registry();
}

tcp_server::tcp_server(asio::io_context& io, int port, node& root):
	io(io),
	root(root),
	acceptor(io, tcp::endpoint(tcp::v4(), port)),
	signals(io)
{
	signals.add(SIGINT);
	signals.add(SIGTERM);

	signals.async_wait(
		[this](boost::system::error_code ec, int signal)
		{
			stop(ec, signal);
		}
	);

	start_listening();

	// TODO: Unhardcode this
	auto new_handle_id = root.get_registry().create();
	make_message(new_handle_id, root.get_pairs());

	broadcast(new_handle_id);
}

void tcp_server::start_listening()
{
	auto connection = tcp_connection::make(io, *this);

	acceptor.async_accept(
		connection->get_socket(),
		[this, connection](boost::system::error_code ec)
		{
			if(!ec)
				connection->start();
			else
				std::cerr << ec.message() << '\n';

			start_listening();
		}
	);
}

void tcp_server::stop(boost::system::error_code, int)
{
	io.stop();
}

void tcp_server::handle(entt::entity message_id, const tcp_connection& connection)
{
	auto& message = root.get_registry().get<message::handle>(message_id);

	auto handle_it = handler_map.find(message.name);

	if(handle_it != handler_map.end())
	{
		(this->*handle_it->second)(connection, *message.data);
	}
}

void tcp_server::handle_pairs(const tcp_connection& connection, const message::pairs& pairs)
{
	if(pairs.jumps_left <= 0)
		return;

	for(const auto& url: pairs.urls)
	{
		std::cerr << url << '\n';
	}

	auto new_message_id = root.get_registry().create();
	auto new_pairs      = pairs;

	new_pairs.jumps_left--;

	make_message(new_message_id, std::move(new_pairs));

	broadcast(new_message_id);
	// TODO: Dont broadcast pairs
}

void tcp_server::handle_transactions(const tcp_connection& connection, const message::transactions& transactions)
{
	if(transactions.jumps_left <= 0)
		return;

    // Ejemplo: Imprimir la información de la transacción
    std::cerr << "Received Transactions:\n";

	// Añadir nuevas transacciones al registro
	for(const auto& tx: transactions.txs)
	{
		entt::entity new_id = root.get_registry().create();
		root.get_registry().emplace<message::transaction>(new_id, tx);
	}

    // Enviar una respuesta al remitente
    auto response_id = root.get_registry().create();
    make_message(response_id, root.get_transactions(transactions.jumps_left-1));
    broadcast(response_id);
}

void tcp_server::connect(const std::string& name, const tcp::resolver::results_type& endpoints, entt::entity message_id)
{
	auto connection = tcp_connection::make(io, *this);

	asio::async_connect(
		connection->get_socket(),
		endpoints,
		[connection, name, message_id](boost::system::error_code ec, const tcp::endpoint&)
		{
			if(!ec)
				connection->start_broadcast(message_id);
			else
				std::cerr << ec.message() << ": " << name << '\n';
		}
	);
}

void tcp_server::broadcast(entt::entity message_id)
{
	auto view = root.get_registry().view<node::url_t, node::endpoints_t>();

	for(auto [_, name, endpoints]: view.each())
	{
		connect(name, endpoints, message_id);
	}
}

}
