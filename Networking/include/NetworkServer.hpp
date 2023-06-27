//
// Created by drping on 6/25/23.
//

#ifndef MYDISCORD_NETWORKSERVER_H
#define MYDISCORD_NETWORKSERVER_H

#include <cstdint>
#include <asio.hpp>
#include <memory>
#include <iostream>
#include "NetworkMessage.hpp"
#include "NetworkQueue.hpp"

namespace Network {
    template<typename T>
    class Server {
    public:
        explicit Server(uint16_t port) : _acceptor(_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {}

        ~Server() { stop(); }

        bool start() {
            try {
                waitForClientConnection();
                _thread = std::thread([this]() { _context.run(); });
            } catch (std::exception &e) {
                std::cerr << "[VoiceServer] error: " << e.what() << std::endl;
                return false;
            }
            std::cout << "[VoiceServer] started successfully" << std::endl;
            return true;
        }

        void stop() {
            _context.stop();
            if (_thread.joinable()) {
                _thread.join();
            }
            std::cout << "[VoiceServer] stopped" << std::endl;
        }

        void waitForClientConnection() {
            this->_acceptor.async_accept([this](std::error_code ec, asio::ip::tcp::socket socket) {
                if (!ec) {
                    std::cout << "[VoiceServer] new connection: " << socket.remote_endpoint() << std::endl;
//            std::shared_ptr<Connection<T>> connection = std::make_shared<Connection<T>>(Connection<T>::owner::server, _context, std::move(socket), _msgIn);
//            if (onClientConnect(connection)) {
//                _connections.push_back(connection);
//                _connections.back()->connectToClient(_idCounter++);
//            } else {
//                std::cerr << "[Sever] connection refused by the client" << std::endl;
//            }
                } else {
                    std::cerr << "[VoiceServer] failed to connect new client " << ec.message() << std::endl;
                }
                waitForClientConnection();
            });
        }

        void messageClient(std::shared_ptr<Connection<T>> client, const Message<T> &msg) {
            if (client && client->isConnected()) {
                client->send(msg);
            } else {
                onClientDisconnect(client);
                client.reset();
                _connections.erase(std::remove(_connections.begin(), _connections.end(), client), _connections);
            }
        }

        void messageAllClients(const Message<T> &msg, std::shared_ptr<Connection<T>> ignore = nullptr) {
            bool isInvalidConnection = false;
            for (std::shared_ptr<Connection<T>> client: _connections) {
                if (client && client->isCOnnected()) {
                    if (client != ignore) {
                        client->send(msg);
                    }
                } else {
                    isInvalidConnection = true;
                    onClientDisconnect(client);
                    client.reset();
                }
            }
            if (isInvalidConnection) {
                _connections.erase(std::remove(_connections.begin(), _connections.end(), nullptr), _connections);
            }
        }

        void update(size_t nbrMsg = -1) {
            size_t msgCount = 0;
            while (msgCount < nbrMsg && !_msgIn.empty()) {
                auto msg = _msgIn.pop_front();
                onMessage(msg._remote, msg._msg);
                msgCount++;
            }
        }

    protected:
        ThreadSafeQueue<MessageDest<T>> _msgIn;
        asio::io_context _context;
        std::thread _thread;
        asio::ip::tcp::acceptor _acceptor;
        uint32_t _idCounter = 0;
        std::deque<std::shared_ptr<Connection<T>>> _connections;

        virtual bool onClientConnect(std::shared_ptr<Connection<T>> client) {
            return false;
        }

        virtual void onClientDisconnect(std::shared_ptr<Connection<T>> client) {};

        virtual void onMessage(std::shared_ptr<Connection<T>> client, Message<T> &msg) {};
    };
}

#endif //MYDISCORD_NETWORKSERVER_H
