#include "collect_transaction.hpp"
#include "mined.hpp"

#include <boost/asio.hpp>

namespace mini_crypto::miner
{

collect_transaction::do_transactions(std::vector<transaction> txs){
    for(const auto& tx : txs){
        verify_transaction(tx);
    }
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

void collect_transaction::add_transaction(const transaction& good_transaction){

    good_txs.push_back(good_transaction);

    if(good_txs.size() == max_transactions_per_block){
        mined mined(good_txs);
    }
}

void collect_transaction::dump(rapidjson::Writer<rapidjson::StringBuffer>& writer) const
{
    writer.StartObject();

    writer.Key("txs");
    writer.StartArray();

	for(const auto& tx: txs)
	{
		tx.dump(writer);
	}

    writer.EndArray();

    writer.EndObject();
}

bool collect_transaction::load(const rapidjson::Value& value)
{
	if(!value.IsObject())
		return false;

	if(auto txs = value.FindMember("txs"); txs != value.MemberEnd() && txs->value.IsArray())
	{
		for(const auto& tx: txs->value.GetArray())
		{
			if(tx.IsObject())
			{
				this->txs.emplace_back().load(tx);
			}
		}
    }

    return true;
}

}