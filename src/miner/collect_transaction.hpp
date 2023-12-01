#pragma once

#include "../node/transaction.hpp"

#include <vector>

namespace mini_crypto::miner
{

class collect_transaction{
private:
    int max_transactions_per_block = 5;
    std::vector<transaction> transactions;
    
    void verify_transaction(const transaction& new_transaction);
    void add_transaction(const transaction& new_transaction);

public:

    collect_transaction(const transaction& new_transaction);

}

}

