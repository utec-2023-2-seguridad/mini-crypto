#include "mined.hpp"

#include <boost/asio.hpp>

namespace mini_crypto::miner
{

collect_transaction::collect_transaction(const transaction& new_transaction){
    verify_transaction(new_transaction);
}

void collect_transaction::verify_transaction(const transaction& new_transaction){
    
    //implementar mecanismos de verificacion de transaccion
    if(new_transaction.amount < 1)
    {
        std::cerr << boost::system::error_code.message() << std::endl;
    }

    //si todo esta bien
    add_transaction(new_transaction);
}

void collect_transaction::add_transaction(const transaction& new_transaction){

    transactions.push_back(new_transaction);

    if(transactions.size() == max_transactions_per_block){
        mined mined(transactions);
    }
}

}