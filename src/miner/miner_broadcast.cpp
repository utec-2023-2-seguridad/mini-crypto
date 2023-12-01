#include "miner_broadcast.hpp"

namespace mini_crypto::miner
{

miner_broadcast::broadcast(const transaction& transaction, const std::string& destinationAddress, int destinationPort){
    tcp::resolver resolver(io);
    tcp::resolver::results_type endpoints = resolver.resolve(destinationAddress, std::to_string(destinationPort));

    boost::asio::connect(socket, endpoints);

    std::string serialized_transaction = serializeTransaction(transaction);
    boost::asio::write(socket, boost::asio::buffer(serializedTransaction + '\n'));

    socket.close();
}

}


