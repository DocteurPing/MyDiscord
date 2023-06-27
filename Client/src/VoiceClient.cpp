//
// Created by drping on 6/27/23.
//

#include "../include/VoiceClient.hpp"

void VoiceClient::pingServer() {
    Network::Message<CustomMsg> msg;
    msg.header.id = CustomMsg::ServerPing;
    std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
    msg << currentTime;
    send(msg);
}

void VoiceClient::processMessages() {
    if (!getQueue().empty()) {
        Network::Message<CustomMsg> msg = getQueue().pop_front()._msg;
        switch (msg.header.id) {
            case CustomMsg::ServerAccept:
                break;
            case CustomMsg::ServerDeny:
                break;
            case CustomMsg::ServerPing: {
                std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
                std::chrono::system_clock::time_point pingTime;
                msg >> pingTime;
                std::cout << "Ping: " << std::chrono::duration<double>(currentTime - pingTime).count()
                          << std::endl;
                break;
            }
            case CustomMsg::MessageAll:
                break;
            case CustomMsg::ServerMessage:
                break;
        }
    }
}
