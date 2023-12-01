#pragma once

#include "../node/transaction.hpp"

#include <boost/asio.hpp>
#include <string>

namespace mini_crypto::miner
{

class miner_broadcast{
private:

    asio::io_context io;
    tcp::socket socket;


public:
    broadcast(const transaction& transaction, const std::string& destinationAddress, int destinationPort);

}

}
