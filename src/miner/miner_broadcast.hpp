#pragma once

#include "../block/block.hpp"

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <string>

namespace mini_crypto::miner
{

class miner_broadcast{
private:

    block my_block

    std::string dump(const block& my_block);

public:

    miner_broadcast(block new_block);

    void broadcast(const block& my_block, const std::string& destination_ip, int destination_port);

}

}
