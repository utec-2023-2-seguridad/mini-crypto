#include "block.hpp"
#include "../block/transaction.hpp"

#include <vector>
#include <string>

namespace mini_crypto::miner
{

collect_transaction::verify_transaction(const transaction& new_transaction){
    //implementar mecanismos de verificacion de transaccion

    if(new_transaction.amount < 1)
    {
        std::cerr << boost::system::error_code.message() << std::endl;
    }

    //si todo esta bien
    add_transaction(new_transaction);
}

collect_transaction::add_transaction(const transaction& new_transaction){
    std::lock_guard<std::mutex> lock(block_transaction);
    
    //aqui deberiamos agregar esta nueva transaccion a la lsita de transacciones
    //solo que nose como hacer para q todos los mineros tengan la misma lista


    miner_broadcast.broadcast(new_transaction);
}

}