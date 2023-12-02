#cmake_minimum_required(VERSION 3.24)
#project(mini-crypto)

set(CMAKE_CXX_STANDARD 17)

#add_executable(mini-crypto container/main.cpp container/blockchain/CBlock.cpp container/blockchain/CChain.cpp)

#find_package(OpenSSL REQUIRED)
#target_link_libraries(mini-crypto OpenSSL::SSL OpenSSL::Crypto)

cmake_minimum_required(VERSION 3.24)

add_executable(mini-crypto src/main.cpp src/blockchain/CBlock.cpp src/blockchain/CChain.cpp)

include(FetchContent)

# Update the commit to point to whatever libsodium-cmake-commit you want to target.
FetchContent_Declare(Sodium
        GIT_REPOSITORY https://github.com/robinlinden/libsodium-cmake.git
        GIT_TAG 99f14233eab1d4f7f49c2af4ec836f2e701c445e # HEAD as of 2022-05-28
)
set(SODIUM_DISABLE_TESTS ON)
FetchContent_MakeAvailable(Sodium)

target_link_libraries(mini-crypto
        PRIVATE
        sodium
)