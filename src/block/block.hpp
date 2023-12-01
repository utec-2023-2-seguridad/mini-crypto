#pragma once

#include "../node/message.hṕp"
#include "block.cpp"


namespace mini_crypto::miner{

class block
{
private:


    block()


public:
    int block_number;
    std::chrono::system_clock::time_point timestamp;
    std::string merkle_root;

    // Datos del Bloque
    std::string previous_block_hash;
    int previous_block_number;
    std::vector<mini_crypto::message::base> transactions;
    std::string block_hash;

    // Información del Minero
    unsigned int nonce;
    std::string miner_address;
    

    // Otras consideraciones
    //int difficultyLevel;


}

}