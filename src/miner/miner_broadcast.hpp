#pragma once

#include "../block/block.hpp"

#include <boost/asio.hpp>
#include <string>

namespace mini_crypto::miner
{

class miner_broadcast{
private:

    //aun nose si usare esto
    asio::io_context io;
    tcp::socket socket;


public:
    miner_broadcast(block new_block);

}

}
