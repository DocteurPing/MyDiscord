//
// Created by drping on 6/26/23.
//

#include "../include/VoiceServer.h"

VoiceServer::VoiceServer(uint16_t port) : Network::Server<ServerMsg>(port) {}

bool VoiceServer::onClientConnect(std::shared_ptr<Network::Connection<ServerMsg>> client) {
    return true;
}

void VoiceServer::onClientDisconnect(std::shared_ptr<Network::Connection<ServerMsg>> client) {
}

void VoiceServer::onMessage(std::shared_ptr<Network::Connection<ServerMsg>> client, Network::Message<ServerMsg> &msg) {
}
