//
// Created by drping on 6/24/23.
//

#include "../include/NetworkClient.h"

template<typename T>
Network::Client<T>::Client() : _socket(_context) {}

template<typename T>
Network::Client<T>::~Client() {
    disconnect();
}

template<typename T>
bool Network::Client<T>::connect(const std::string &host, const uint16_t port) {
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

template<typename T>
void Network::Client<T>::disconnect() {
    if (_connection) {
        _connection->disconnect();
    }
    _context.stop();
    if (_thread.joinable()) {
        _thread.join();
    }
    _connection.release();
}

template<typename T>
bool Network::Client<T>::isConnected() {
    return _connection && _connection->isConnected();
}

template<typename T>
Network::ThreadSafeQueue<Network::MessageDest<T>> &Network::Client<T>::getQueue() {
    return _msgIn;
}