//
// Created by drping on 6/24/23.
//

#include <iostream>
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include "Networking/include/NetworkMessage.h"
#include "Networking/include/NetworkQueue.h"

enum class MsgType : uint32_t {
    Test,
    TOTO
};

int main() {
    Network::message<MsgType> msg;
    msg.header.id = MsgType::TOTO;

    int a = 1;
    bool b = true;
    float c = 3.14;
    struct {
        float x;
        float y;
    } d[5];
    msg << a << b << c << d;
    a = 99;
    b = false;
    c = 99.0f;

    std::cout << msg << std::endl;
    return 0;
}