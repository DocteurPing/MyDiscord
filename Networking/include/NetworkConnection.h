//
// Created by drping on 6/24/23.
//

#ifndef MYDISCORD_NETWORKCONNECTION_H
#define MYDISCORD_NETWORKCONNECTION_H

#include <memory>
#include <asio.hpp>
#include "NetworkQueue.h"
#include "NetworkMessage.h"

namespace Network {
    template<typename T>
    class Connection : public std::enable_shared_from_this<Connection<T>> {
    public:
        Connection() = default;
        ~Connection() = default;

        bool connectToServer();
        bool disconnect();
        bool isConnected() const;
        bool send(const message<T> &msg);

    protected:
        asio::ip::tcp::socket _socket;
        asio::io_context &_asioContext;
        ThreadSafeQueue<message<T>> &msgOut;
        ThreadSafeQueue<messageDest<T>> &msgIn;
    };
}

#endif //MYDISCORD_NETWORKCONNECTION_H
