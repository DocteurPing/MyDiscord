//
// Created by drping on 6/25/23.
//

#ifndef MYDISCORD_NETWORKSERVER_H
#define MYDISCORD_NETWORKSERVER_H

#include <cstdint>
#include <asio.hpp>
#include <memory>
#include <iostream>
#include "NetworkMessage.h"
#include "NetworkQueue.h"

namespace Network {
    template<typename T>
    class Server {
    public:
        explicit Server(uint16_t port);

        ~Server();

        bool start();

        void stop();

        void waitForClientConnection();

        void messageClient(std::shared_ptr<Connection<T>> client, const Message<T> &msg);

        void messageAllClients(const Message<T> &msg, std::shared_ptr<Connection<T>> ignore = nullptr);

        void update(size_t nbrMsg = -1);

    protected:
        ThreadSafeQueue<MessageDest<T>> _msgIn;
        asio::io_context _context;
        std::thread _thread;
        asio::ip::tcp::acceptor _acceptor;
        uint32_t _idCounter = 0;
        std::deque<std::shared_ptr<Connection<T>>> _connections;

        virtual bool onClientConnect(std::shared_ptr<Connection<T>> client);

        virtual void onClientDisconnect(std::shared_ptr<Connection<T>> client);

        virtual void onMessage(std::shared_ptr<Connection<T>> client, Message<T> &msg);
    };
}

#endif //MYDISCORD_NETWORKSERVER_H
