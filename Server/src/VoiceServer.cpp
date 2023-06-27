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
}
