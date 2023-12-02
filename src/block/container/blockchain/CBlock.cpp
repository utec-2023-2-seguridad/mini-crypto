#include "CBlock.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sodium.h>

using namespace blockchain;
using namespace std;

/*
CBlock::CBlock(CBlock *prevBlock)
{
    mPrevBlock = prevBlock;
    memset(mHash, SHA256_DIGEST_LENGTH, 0);
    if(mPrevBlock){
        memcpy(mPrevHash, mPrevBlock->getHash(), SHA256_DIGEST_LENGTH);
    }
    else{
        memset(mPrevHash, SHA256_DIGEST_LENGTH, 0);
    }
    mCreatedTS = time(0);
    mNonce = 0;
    mDataSize = 0;
    mData = 0;
    calculateHash();
}
*/
CBlock::CBlock(CBlock *prevBlock) {
    mPrevBlock = prevBlock;
    memset(mHash, crypto_hash_sha256_BYTES, 0);
    if (mPrevBlock) {
        memcpy(mPrevHash, mPrevBlock->getHash(), crypto_hash_sha256_BYTES);
    } else {
        memset(mPrevHash, crypto_hash_sha256_BYTES, 0);
    }
    mCreatedTS = time(0);
    mNonce = 0;
    mDataSize = 0;
    mData = nullptr;
    calculateHash();
}

/*
void CBlock::calculateHash()
{
    uint32_t sz = (SHA256_DIGEST_LENGTH * sizeof(uint8_t)) + sizeof(time_t) + mDataSize + sizeof(uint32_t);

    uint8_t* buf = new uint8_t[sz];
    uint8_t* ptr = buf;

    memcpy(ptr, mPrevHash, SHA256_DIGEST_LENGTH * sizeof(uint8_t));
    ptr += SHA256_DIGEST_LENGTH * sizeof(uint8_t);
    memcpy(ptr, &mCreatedTS, sizeof(time_t));
    ptr += sizeof(time_t);
    if(mDataSize != 0)
    {
        memcpy(ptr, mData, mDataSize);
        ptr += mDataSize;
    }
    memcpy(ptr, &mNonce, sizeof(uint32_t));
    ptr += sizeof(uint32_t);

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, buf, sz);
    SHA256_Final(mHash, &sha256);

}
*/
void CBlock::calculateHash()
{
    uint32_t sz = (crypto_hash_sha256_BYTES * sizeof(uint8_t)) + sizeof(time_t) + mDataSize + sizeof(uint32_t);

    uint8_t* buf = new uint8_t[sz];
    uint8_t* ptr = buf;

    memcpy(ptr, mPrevHash, crypto_hash_sha256_BYTES * sizeof(uint8_t)); // Cambia a crypto_hash_sha256_BYTES
    ptr += crypto_hash_sha256_BYTES * sizeof(uint8_t);
    memcpy(ptr, &mCreatedTS, sizeof(time_t));
    ptr += sizeof(time_t);
    if (mDataSize != 0)
    {
        memcpy(ptr, mData, mDataSize);
        ptr += mDataSize;
    }
    memcpy(ptr, &mNonce, sizeof(uint32_t));
    ptr += sizeof(uint32_t);

    crypto_hash_sha256(mHash, buf, sz); // Cambia a crypto_hash_sha256

    delete[] buf;
}


uint8_t* CBlock::getHash() {
    return mHash;
}

/*
std::string CBlock::getHashStr()
{
    char buf[SHA256_DIGEST_LENGTH * 2 + 1];
    for(uint32_t n=0; n < SHA256_DIGEST_LENGTH; n++){
        sprintf(buf + (n*2), "%02x", mHash[n]);
    }
    buf[SHA256_DIGEST_LENGTH * 2] = 0;
    return std::string(buf);
}
*/
std::string CBlock::getHashStr()
{
    char buf[crypto_hash_sha256_BYTES * 2 + 1];
    for (size_t n = 0; n < crypto_hash_sha256_BYTES; n++) {
        snprintf(buf + (n * 2), 3, "%02x", mHash[n]);
    }
    buf[crypto_hash_sha256_BYTES * 2] = 0;
    return std::string(buf);
}

CBlock* CBlock::getPrevBlock()
{
    return mPrevBlock;
}

void CBlock::appendData(uint8_t* data, uint32_t size)
{
    uint8_t* newData = new uint8_t[mDataSize + size];
    uint8_t* ptr = newData;
    if(mDataSize != 0){
        memcpy(ptr, mData, mDataSize);
        ptr += mDataSize;
        delete[] mData;
    }
    memcpy(ptr, data, size);
    mData = newData;
    mDataSize += size;
}

bool CBlock::isDifficulty(int difficulty)
{
    for(uint32_t n=0; n < difficulty; n++){
        if(mHash[n] != 0){
            return false;
        }
    }
    return true;
}

void CBlock::mine(int difficulty)
{
    while(!isDifficulty(difficulty)){
        mNonce++;
        calculateHash();
        usleep(10);
    }
}

uint32_t CBlock::getNonce() {
    return mNonce;
}

