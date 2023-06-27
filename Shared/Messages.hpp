//
// Created by drping on 6/27/23.
//

#ifndef MYDISCORD_MESSAGES_HPP
#define MYDISCORD_MESSAGES_HPP

#include <cstdint>

enum class CustomMsg : uint32_t {
    ServerAccept,
    ServerDeny,
    ServerPing,
    MessageAll,
    ServerMessage
};

#endif //MYDISCORD_MESSAGES_HPP
