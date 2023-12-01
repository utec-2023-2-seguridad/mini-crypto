#include <vector>
#include <chrono>
#include <openssl/sha.h>

namespace mini_crypto::miner{
    block::block(){
        this->timestamp = std::chrono::system_clock::now();
    }
}