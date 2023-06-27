//
// Created by drping on 6/27/23.
//


#include "../include/VoiceClient.hpp"

int main() {
    VoiceClient client;
    client.connect("127.0.0.1", 50000);
    bool serverUp = true;
    while (serverUp) {
        if (client.isConnected()) {
            client.pingServer();
            client.processMessages();
        } else {
            std::cout << "[VoiceClient] Server down" << std::endl;
            serverUp = false;
        }
    }
    return 0;
}