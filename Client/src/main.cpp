//
// Created by drping on 6/27/23.
//


#include "../include/VoiceClient.hpp"

int main() {
    VoiceClient client;
    client.connect("127.0.0.1", 50000);
    return 0;
}