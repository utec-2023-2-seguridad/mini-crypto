#include "blockchain/CChain.h"
#include <iostream>

using namespace std;
using namespace blockchain;

int main(int argc, char **argv) {
    cout << "Start.\n";

    CChain chain(1); //Esto ayuda a determinar la dificultad
    cout << "Chain initialized!\n";

    int n = 5;

    for (int i = 0; i < n; i++) {
        CBlock* currentBlock = chain.getCurrentBlock();

        uint8_t* garbage = new u_int8_t[32];
        for (uint32_t j = 0; j < 32; j++) {
            garbage[j] = time(0) % 255;
        }
        cout << "Garbage generated.\n";

        chain.appendToCurrentBlock(garbage, 32);
        delete[] garbage;

        cout << "Garbage appended to current block.\n";

        chain.nextBlock();

        cout << "Next block mined.\n";
        cout << "Previous Hash: " << currentBlock->getHashStr() << "\nNonce: " << currentBlock->getNonce() << endl;
    }

    return 0;
}