#pragma once

#include "../node/message/transaction.hpp"
#include "../block/block.hpp"
#include "../blockchain/blockchain.hpp"

#include <string>
#include <vector>

namespace mini_crypto::miner
{

class mined{
private:
    block new_block;
    block last_block;
    std::vector<std::string> hash_txs:
    std::string merkle_root;
    unsigned int nonce;
    std::string miner_address;

    void last_block(blockchain bc);
    //nose cual deberia usar
    std::string sha256(const std::string& input);
    void hash_transactions(std::vector<transaction> transactions);
    void hash_transactions_rapid_json();
    void generate_merkle_root(std::vector<transaction> hash_txs);
    void get_my_info();
    void generate_block();
    void broadcast(block new_block);
public:
    mined(std::vector<transaction> transactions);
    void undermine();
}

}
