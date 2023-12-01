#include "miner_broadcast.hpp"

namespace mini_crypto::miner
{

miner_broadcast::miner_broadcast(block new_block){

    //realizar broadcast

    //esto era una logica que tenia antes pero nose aun muy bien como hacer el broadasct del bloque
    /*
    tcp::resolver resolver(io);
    tcp::resolver::results_type endpoints = resolver.resolve(destinationAddress, std::to_string(destinationPort));

    boost::asio::connect(socket, endpoints);

    std::string serialized_transaction = serializeTransaction(transaction);
    boost::asio::write(socket, boost::asio::buffer(serializedTransaction + '\n'));

    socket.close();*/
}

}


