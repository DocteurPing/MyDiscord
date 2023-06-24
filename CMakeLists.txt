cmake_minimum_required(VERSION 3.25)
project(MyDiscord)

set(CMAKE_CXX_STANDARD 17)

add_executable(MyDiscord
        main.cpp
        Networking/include/NetworkMessage.h
        Networking/include/NetworkQueue.h
        Networking/include/NetworkConnection.h
        Networking/include/NetworkClient.h Networking/src/NetworkClient.cpp Networking/src/NetworkQueue.cpp)
