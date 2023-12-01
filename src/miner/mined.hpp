#pragma once

#include "../node/transaction.hpp"
#include "../block/block.hpp"

#include <vector>

namespace mini_crypto::miner
{

class mined{
private:
    block new_block;

    block get_block(std::vector<transaction> transactions);
    void broadcast(block new_block);
public:
    mined(std::vector<transaction> transactions);
}

}
