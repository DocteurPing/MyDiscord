//
// Created by drping on 6/24/23.
//

#ifndef MYDISCORD_NETWORKCLIENT_H
#define MYDISCORD_NETWORKCLIENT_H

#include <asio.hpp>
#include <iostream>
#include "NetworkMessage.h"
#include "NetworkQueue.h"

namespace Network {
    template<typename T>
    class Client {
        Client() : _socket(_context) {}
        ~Client() {
            disconnect();
        }

    public:
        bool connect(const std::string &host, uint16_t port);
        void disconnect();
        bool isConnected();
        ThreadSafeQueue<messageDest<T>> &getQueue();

    protected:
        asio::io_context _context;
        std::thread _thread;
        asio::ip::tcp::socket _socket;
        std::unique_ptr<Connection<T>> _connection;

    private:
        ThreadSafeQueue<messageDest<T>> _msgIn;
    };
}

#endif //MYDISCORD_NETWORKCLIENT_H