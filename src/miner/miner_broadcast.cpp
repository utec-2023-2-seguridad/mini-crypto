#include "miner_broadcast.hpp"

namespace mini_crypto::miner
{

miner_broadcast::miner_broadcast(block new_block){
    my_block = new_block;
}

std::string miner_broadcast::dump(const block& my_block){
    rapidjson::StringBuffer s;
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);
    
    writer.StartObject();

    writer.Key("block_number");
    writer.Int(my_block.block_number);

    writer.Key("previous_block_hash");
    writer.String(my_block.previous_block_hash.c_str());

    writer.Key("merkle_root");
    writer.String(my_block.merkle_root.c_str());

    writer.Key("nonce");
    writer.Uint(my_block.nonce);

    writer.Key("miner_address");
    writer.String(my_block.miner_address.c_str());

    writer.Key("block_hash");
    writer.String(my_block.block_hash.c_str());

    
    writer.EndObject();

    return s.GetString();
}

void miner_broadcast::broadcast(const block& my_block, const std::string& destination_ip, int destination_port) {
        // Serializar el bloque
        std::string serialized_block = dump(my_block);

        // Construir el comando netcat y transmitir la cadena serializada
        std::string nc_command = "echo -n '" + serialized_block + "' | nc " + destination_ip + " " + std::to_string(destination_port);
        system(nc_command.c_str());
    }
}


