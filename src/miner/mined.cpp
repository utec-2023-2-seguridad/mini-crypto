#include "mined.hpp"
#include "miner_broadcast.hpp"

#include <openssl/sha.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <string.h>
#include <chrono>

namespace mini_crypto::miner
{

void mined::last_block(blockchain bc){
    //obtener el ultimo bloque del blockchain
    if(bc.size() == 0){
        last_block.block_number = 0;
        last_block.previous_block_hash = sha256("Start blockchain");
    }else{ // en el mejor de los casos si usamos emplace_back creo deberia ser
        last_block = bc[0];
    }
}

void mined::hash_transactions(std::vector<transaction> transactions){
    for (const auto& tx : transactions) {
        
        std::string tx_string = tx.sender + " - " + tx.receiver + " - " + to_string(amount);

        // Calculamos el hash SHA-256
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256(reinterpret_cast<const unsigned char*>(tx_string.c_str()), tx_string.length(), hash);

        // Convertimos el hash a una cadena hexadecimal
        std::stringstream ss;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
        }

        hash_txs.push_back(ss.str());
}
}

void mined::hash_transactions_rapid_json(){

    for (const auto& tx : transactions) {
        // Obtenemos una representación en cadena de la transacción usando RapidJSON
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        tx.dump(writer);

        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256(reinterpret_cast<const unsigned char*>(buffer.GetString()), buffer.GetSize(), hash);

        std::stringstream ss;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
        }

        hash_txs.push_back(ss.str());
    }

}

void mined::generate_merkle_root(std::vector<transaction> hash_txs){
    if (hash_txs.empty()) {
        // Manejar el caso cuando no hay transacciones
        return;
    }

    std::vector<std::string> merkle_tree = hash_txs;

    // Construir el árbol de Merkle
    while (merkle_tree.size() > 1) {
        // Combinar pares de hashes consecutivos y calcular su hash
        std::vector<std::string> new_tree;

        for (int i = 0; i < merkle_tree.size(); i += 2) {
            // Si hay un número impar de nodos, duplicar el último nodo
            const std::string& left_hash = merkle_tree[i];
            const std::string& right_hash = (i + 1 < merkle_tree.size()) ? merkle_tree[i + 1] : merkle_tree[i];
            
            std::string combined_hash = sha256(left_hash + right_hash);
            new_tree.push_back(combined_hash);
        }

        merkle_tree = new_tree;
    }

    // El último elemento en merkle_tree es la raíz de Merkle
    new_block.merkle_root = merkle_tree[0];
    }


void mined::get_my_info(){
    nonce = 0;
    miner_address = "minero";
}

void mined::generate_block(){
    new_block.block_number = ++last_block.block_number;
    new_block.previous_block_hash = last_block.block_hash;
    new_block.merkle_root = merkle_root;
    new_block.noce = nonce;
    new_block.miner_address = miner_address;
}

void mined::broadcast(block new_block){
    miner_broadcast broasdacast(new_block);
}

void mined::undermine(){
    blockchain bc;
    last_block(bc);
    generate_merkle_root(hash_txs);
    get_my_info();
    generate_block();

    std::string initial_hash = new_block.previous_block_hash + new_block.merkle_root;

    while (true) {
        // Combinar el hash inicial con el nonce actual
        std::string hash_attempt = sha256(initial_hash + std::to_string(new_block.nonce));

        // Verificar si el hash cumple con ciertos requisitos (por ejemplo, comienza con varios ceros)
        if (hash_attempt.substr(0, 2) == "00") {
            // Se encontró un nonce que cumple con los requisitos, asignar a new_block.nonce
            new_block.block_hash = hash_attempt;
            new_block.timestamp = std::chrono::system_clock::now();
            broadcast(new_block);
            break;
        }

        // Incrementar el nonce para la siguiente iteración
        ++new_block.nonce;
    }
    
}

mined::mined(std::vector<transaction> transactions){
    hash_transactions(transactions);
}

}