//
// Created by drping on 6/26/23.
//

#include "../include/VoiceServer.hpp"

VoiceServer::VoiceServer(uint16_t port) : Network::Server<CustomMsg>(port) {}

bool VoiceServer::onClientConnect(std::shared_ptr<Network::Connection<CustomMsg>> client) {
    return true;
}

void VoiceServer::onClientDisconnect(std::shared_ptr<Network::Connection<CustomMsg>> client) {
}

void VoiceServer::onMessage(std::shared_ptr<Network::Connection<CustomMsg>> client, Network::Message<CustomMsg> &msg) {
    switch (msg.header.id) {
        case CustomMsg::ServerAccept:
            break;
        case CustomMsg::ServerDeny:
            break;
        case CustomMsg::ServerPing: {
            std::cout << "[" << client->getId() << "]: Server Ping" << std::endl;
            client->send(msg);
            break;
        }
        case CustomMsg::MessageAll:
            break;
        case CustomMsg::ServerMessage:
            break;
    }
}
