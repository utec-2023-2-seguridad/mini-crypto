#include "mined.hpp"
#include "miner_broadcast.hpp"

namespace mini_crypto::miner
{

mined::mined(std::vector<transaction> transactions){
    block new_block = get_block(transactions);

    //si todo bien hacer broadcast
    broadcast(new_block);
}

block mined::get_block(std::vector<transaction> transactions){
    //falta implementar la magia del minado
}

void mined::broadcast(block new_block){
    miner_broadcast broasdacast(new_block);
}

}