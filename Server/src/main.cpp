//
// Created by drping on 6/26/23.
//

#include "../include/VoiceServer.hpp"

int main() {
    VoiceServer server(50000);
    server.start();
    while (1) {
        server.update();
    }
    return 0;
}