//
// Created by drping on 6/26/23.
//

#ifndef MYDISCORD_VOICESERVER_HPP
#define MYDISCORD_VOICESERVER_HPP

#include "../../Networking/include/NetworkServer.hpp"
#include "../../Shared/Messages.hpp"

class VoiceServer : public Network::Server<CustomMsg> {

public:
    explicit VoiceServer(uint16_t port);

protected:
    bool onClientConnect(std::shared_ptr<Network::Connection<CustomMsg>> client) override;

    void onClientDisconnect(std::shared_ptr<Network::Connection<CustomMsg>> client) override;

    void onMessage(std::shared_ptr<Network::Connection<CustomMsg>> client, Network::Message<CustomMsg> &msg) override;
};


#endif //MYDISCORD_VOICESERVER_HPP
