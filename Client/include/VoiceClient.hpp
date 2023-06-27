//
// Created by drping on 6/27/23.
//

#ifndef MYSERVER_VOICECLIENT_HPP
#define MYSERVER_VOICECLIENT_HPP

#include "../Networking/include/NetworkClient.hpp"
#include "../Shared/Messages.hpp"

class VoiceClient : public Network::Client<CustomMsg> {
public:
    void pingServer();

    void processMessages();
};


#endif //MYSERVER_VOICECLIENT_HPP
