#ifndef __C_BLOCK_INCLUDED__
#define __C_BLOCK_INCLUDED__
#include <string>
//#include <openssl/sha.h>
#include <sodium.h>

using namespace std;
/*
namespace blockchain
{
    class CBlock
    {
    private:
        uint8_t mHash[SHA256_DIGEST_LENGTH];
        uint8_t mPrevHash[SHA256_DIGEST_LENGTH];
        CBlock* mPrevBlock;
        uint8_t* mData;
        uint32_t mDataSize;
        time_t mCreatedTS;
        uint32_t mNonce;
    public:
        CBlock(CBlock *prevBlock);
        void calculateHash();
        uint8_t* getHash();
        std::string getHashStr();
        CBlock* getPrevBlock();
        void appendData(uint8_t* data, uint32_t size);
        bool isDifficulty(int difficulty);
        void mine(int difficulty);
        uint32_t getNonce();
    };
}
*/
namespace blockchain
{
    class CBlock
    {
    private:
        uint8_t mHash[crypto_hash_sha256_BYTES]; // Cambia a crypto_hash_sha256_BYTES
        uint8_t mPrevHash[crypto_hash_sha256_BYTES]; // Cambia a crypto_hash_sha256_BYTES
        CBlock* mPrevBlock;
        uint8_t* mData;
        uint32_t mDataSize;
        time_t mCreatedTS;
        uint32_t mNonce;
    public:
        CBlock(CBlock *prevBlock);
        void calculateHash();
        uint8_t* getHash();
        std::string getHashStr();
        CBlock* getPrevBlock();
        void appendData(uint8_t* data, uint32_t size);
        bool isDifficulty(int difficulty);
        void mine(int difficulty);
        uint32_t getNonce();
    };
}

#endif