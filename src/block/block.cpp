#pragma once

#include "../node/message/transaction.hpp"

#include <vector>
#include <chrono>
#include <string>


namespace mini_crypto::block{

struct block
{
    // Datos del Bloque
    int block_number = 0;
    std::string previous_block_hash;

    //logica de obtencion en el minado
    std::string merkle_root;

    // Información del Minero
    unsigned int nonce;
    std::string miner_address;

    //bloque en blockchain
    std::string block_hash;
    std::chrono::system_clock::time_point timestamp;

}

}