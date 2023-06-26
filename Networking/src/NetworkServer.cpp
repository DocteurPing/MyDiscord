//
// Created by drping on 6/25/23.
//

#include "../include/NetworkServer.h"

template<typename T>
Network::Server<T>::Server(uint16_t port) : _acceptor(_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {
}

template<typename T>
Network::Server<T>::~Server() {
    stop();
}

template<typename T>
void Network::Server<T>::waitForClientConnection() {
    _acceptor.async_accept([this](std::error_code &ec, asio::ip::tcp::socket &socket) {
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

template<typename T>
void Network::Server<T>::messageClient(std::shared_ptr<Connection<T>> client, const Message<T> &msg) {
    if (client && client->isConnected()) {
        client->send(msg);
    } else {
        onClientDisconnect(client);
        client.reset();
        _connections.erase(std::remove(_connections.begin(), _connections.end(), client), _connections);
    }
}

template<typename T>
void Network::Server<T>::messageAllClients(const Message<T> &msg, std::shared_ptr<Connection<T>> ignore) {
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

template<typename T>
void Network::Server<T>::update(size_t nbrMsg) {
    size_t msgCount = 0;
    while (msgCount < nbrMsg && !_msgIn.empty()) {
        auto msg = _msgIn.pop_front();
        onMessage(msg._remote, msg._msg);
        msgCount++;
    }
}

template<typename T>
bool Network::Server<T>::onClientConnect(std::shared_ptr<Connection<T>> client) {
    return false;
}

template<typename T>
void Network::Server<T>::onClientDisconnect(std::shared_ptr<Connection<T>> client) {

}

template<typename T>
void Network::Server<T>::onMessage(std::shared_ptr<Connection<T>> client, Message<T> &msg) {

}

template<typename T>
bool Network::Server<T>::start() {
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

template<typename T>
void Network::Server<T>::stop() {
    _context.stop();
    if (_thread.joinable()) {
        _thread.join();
    }
    std::cout << "[VoiceServer] stopped" << std::endl;
}