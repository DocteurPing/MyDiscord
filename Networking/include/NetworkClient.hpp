//
// Created by drping on 6/24/23.
//

#ifndef MYDISCORD_NETWORKCLIENT_H
#define MYDISCORD_NETWORKCLIENT_H

#include <asio.hpp>
#include <iostream>
#include "NetworkMessage.hpp"
#include "NetworkQueue.hpp"

namespace Network {
    template<typename T>
    class Client {
        Client() : _socket(_context) {}

        ~Client() { disconnect(); }

    public:
        bool connect(const std::string &host, const uint16_t port) {
            try {
                _connection = std::make_unique<Connection<T>>();
                asio::ip::tcp::resolver resolver(_context);
                auto endpoints = resolver.resolve(host, std::to_string(port));
                _connection->connectToServer(endpoints);
                _thread = std::thread([this]() { _context.run(); });
            } catch (std::exception &e) {
                std::cerr << "Couldn't connect to host: " << e.what() << std::endl;
                return false;
            }
            return true;
        }

        void disconnect() {
            if (_connection) {
                _connection->disconnect();
            }
            _context.stop();
            if (_thread.joinable()) {
                _thread.join();
            }
            _connection.release();
        }

        bool isConnected() {
            return _connection && _connection->isConnected();
        }

        ThreadSafeQueue<MessageDest<T>> &getQueue() {
            return _msgIn;
        }

    protected:
        asio::io_context _context;
        std::thread _thread;
        asio::ip::tcp::socket _socket;
        std::unique_ptr<Connection<T>> _connection;

    private:
        ThreadSafeQueue<MessageDest<T>> _msgIn;
    };
}

#endif //MYDISCORD_NETWORKCLIENT_H
