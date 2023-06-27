//
// Created by drping on 6/24/23.
//

#ifndef MYDISCORD_NETWORKCONNECTION_H
#define MYDISCORD_NETWORKCONNECTION_H

#include <memory>
#include <asio.hpp>
#include "NetworkQueue.hpp"
#include "NetworkMessage.hpp"

namespace Network {
    template<typename T>
    class Connection : public std::enable_shared_from_this<Connection<T>> {
    public:

        enum class Owner {
            Client,
            Server
        };

        Connection(Owner owner, asio::io_context &context, asio::ip::tcp::socket socket,
                   ThreadSafeQueue<MessageDest<T>> &msgIn) : _owner(owner), _asioContext(context),
                                                             _socket(std::move(socket)), _msgIn(msgIn) {}

        ~Connection() = default;

        void connectToServer(const asio::ip::tcp::resolver::results_type &endpoints) {
            if (_owner == Owner::Client) {
                asio::async_connect(_socket, endpoints,
                                    [this](std::error_code ec, const asio::ip::tcp::endpoint &endpoint) {
                                        if (!ec) {
                                            readHeader();
                                        }
                                    });
            }
        }

        void disconnect() {
            if (isConnected()) {
                asio::post(_asioContext, [this]() { _socket.close(); });
            }
        }

        [[nodiscard]] bool isConnected() const {
            return _socket.is_open();
        }

        void send(const Message<T> &msg) {
            asio::post(_asioContext, [this, msg]() {
                bool isQueueEmpty = _msgOut.empty();
                _msgOut.push_back(msg);
                if (isQueueEmpty) {
                    writeHeader();
                }
            });
        }

        [[nodiscard]] uint32_t getId() const {
            return _id;
        }

        void connectToClient(uint32_t id = 0) {
            if (_owner == Owner::Server) {
                if (_socket.is_open()) {
                    _id = id;
                    readHeader();
                }
            }
        }

    protected:
        asio::ip::tcp::socket _socket;
        asio::io_context &_asioContext;
        ThreadSafeQueue<Message<T>> _msgOut;
        ThreadSafeQueue<MessageDest<T>> &_msgIn;
        Owner _owner = Owner::Server;
        uint32_t _id = 0;
        Message<T> currentMsg;

    private:
        void readHeader() {
            asio::async_read(_socket, asio::buffer(&currentMsg.header, sizeof(MessageHeader<T>)),
                             [this](std::error_code ec, std::size_t length) {
                                 if (!ec) {
                                     if (currentMsg.header.size > 0) {
                                         currentMsg.body.resize(currentMsg.header.size);
                                         readBody();
                                     } else {
                                         addMsgToQueue();
                                     }
                                 } else {
                                     std::cerr << "[" << _id << "] Read header failed: " << ec.message() << std::endl;
                                     _socket.close();
                                 }
                             });
        }

        void readBody() {
            asio::async_read(_socket, asio::buffer(currentMsg.body.data(), currentMsg.header.size),
                             [this](std::error_code ec, std::size_t length) {
                                 if (!ec) {
                                     addMsgToQueue();
                                 } else {
                                     std::cerr << "[" << _id << "] Read body failed: " << ec.message() << std::endl;
                                     _socket.close();
                                 }
                             });
        }

        void addMsgToQueue() {
            _msgIn.push_back({_owner == Owner::Server ? this->shared_from_this() : nullptr, currentMsg});
            readHeader();
        }

        void writeHeader() {
            asio::async_write(_socket, asio::buffer(&_msgOut.front().header, sizeof(MessageHeader<T>)),
                              [this](asio::error_code ec, std::size_t length) {
                                  if (!ec) {
                                      if (_msgOut.front().body.size() > 0) {
                                          writeBody();
                                      } else {
                                          _msgOut.pop_front();
                                          writeHeader();
                                      }
                                  } else {
                                      std::cerr << "[" << _id << "] Write header failed: " << ec.message() << std::endl;
                                      _socket.close();
                                  }
                              });
        }

        void writeBody() {
            asio::async_write(_socket, asio::buffer(_msgOut.front().body.data(), _msgOut.front().header.size),
                              [this](asio::error_code ec, std::size_t length) {
                                  if (!ec) {
                                      if (!_msgOut.empty()) {
                                          writeHeader();
                                      }
                                  } else {
                                      std::cerr << "[" << _id << "] Write body failed: " << ec.message() << std::endl;
                                      _socket.close();
                                  }
                              });
        }
    };
}

#endif //MYDISCORD_NETWORKCONNECTION_H
