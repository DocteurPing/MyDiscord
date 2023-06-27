//
// Created by drping on 6/26/23.
//

#ifndef MYDISCORD_VOICESERVER_H
#define MYDISCORD_VOICESERVER_H

#include <cstdint>
#include "../../Networking/include/NetworkServer.hpp"

enum class ServerMsg : uint32_t {
    ServerAccept,
    ServerDeny,
    ServerPing,
    MessageAll,
    ServerMessage
};

class VoiceServer : public Network::Server<ServerMsg> {

public:
    explicit VoiceServer(uint16_t port);

protected:
    bool onClientConnect(std::shared_ptr<Network::Connection<ServerMsg>> client) override;

    void onClientDisconnect(std::shared_ptr<Network::Connection<ServerMsg>> client) override;

    void onMessage(std::shared_ptr<Network::Connection<ServerMsg>> client, Network::Message<ServerMsg> &msg) override;
};


#endif //MYDISCORD_VOICESERVER_H
