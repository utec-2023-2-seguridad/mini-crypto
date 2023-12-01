#pragma once

#include "../node/message/transaction.hpp"

#include <vector>
#include <chrono>
#include <string>


namespace mini_crypto::miner{

struct block
{
    int block_number;
    std::chrono::system_clock::time_point timestamp;

    //logica de obtencion en el minado
    std::string merkle_root;

    // Datos del Bloque
    std::string previous_block_hash;
    int previous_block_number;
    std::string block_hash;

    // Información del Minero
    unsigned int nonce;
    std::string miner_address;


    //aun estoy pensado  esta parte...
    block(std::vector<transaction> transactions)

}

}