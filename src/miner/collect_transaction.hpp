#pragma once

#include "../node/message/base.hpp"
#include "../node/message/transaction.hpp"
#include "../node/message/transactions.hpp"

#include <vector>

namespace mini_crypto::miner
{

class collect_transaction: public base{
private:
    int max_transactions_per_block = 5;
    std::vector<transaction> good_txs;
    
    void do_transactions(std::vector<transaction> txs);
    void verify_transaction(const transaction& new_transaction);
    void add_transaction(const transaction& new_transaction);

public:
    std::vector<transaction> txs;

    collect_transaction(){};

    // Métodos para serialización y deserialización
    void dump(rapidjson::Writer<rapidjson::StringBuffer>& writer) const;
    bool load(const rapidjson::Value& value);

}

}

