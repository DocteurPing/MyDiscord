//
// Created by drping on 6/26/23.
//

#include "../include/VoiceServer.h"

int main() {
    VoiceServer server((uint16_t) 50000);
    server.start();
    while (1) {
        server.update();
    }
    return 0;
}