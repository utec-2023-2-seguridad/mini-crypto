cmake_minimum_required(VERSION 3.24)
project(mini-crypto)

set(CMAKE_CXX_STANDARD 17)

add_executable(mini-crypto container/main.cpp container/blockchain/CBlock.cpp container/blockchain/CChain.cpp)

find_package(OpenSSL REQUIRED)
target_link_libraries(mini-crypto OpenSSL::SSL OpenSSL::Crypto)
