#pragma once

#include "../node/node.hpp"
#include "../node/message.hṕp"
#include "miner_broadcast.hpp"

#include <mutex>

namespace mini_crypto::miner
{

class collect_transaction{
private:
    std::string hash_transaction;
    std::mutex block_transaction;

public:

    void verify_transaction(const transaction& new_transaction);
    void add_transaction(const transaction& new_transaction);

}

}

