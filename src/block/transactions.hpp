#pragma once

#include "../miner/collect_transaction"
#include "../node/transaction"
#include <vector>

namespace mini_crypto::block
{

struct transactions{
    int max_transactions_per_block = 5;
    std::vector<transaccion> transactions;

}

}