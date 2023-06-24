//
// Created by drping on 6/24/23.
//

#ifndef MYDISCORD_NETWORKMESSAGE_H
#define MYDISCORD_NETWORKMESSAGE_H

#include <cstdint>
#include <vector>
#include <ostream>
#include <cstring>

namespace Network {
    template<typename T>
    struct messageHeader {
        T id{};
        uint32_t size = 0;
    };

    template<typename T>
    struct message {
        messageHeader<T> header{};
        std::vector<uint8_t> body;

        [[nodiscard]] std::size_t size() const {
            return sizeof(messageHeader<T>) + body.size();
        }

        friend std::ostream &operator<<(std::ostream &os, const message<T> &msg) {
            os << "Message Id:" << static_cast<int>(msg.header.id) << " Size:" << msg.header.size;
            return os;
        }

        template<typename DataType>
        friend message<T> &operator<<(message<T> &msg, const DataType &data) {
            static_assert(std::is_standard_layout<DataType>::value, "Cannot serialize the data");
            size_t i = msg.body.size();
            msg.body.resize(msg.body.size() + sizeof(DataType));
            std::memcpy(msg.body.data() + i, &data, sizeof(DataType));
            msg.header.size = msg.size();
            return msg;
        }

        template<typename DataType>
        friend message<T> &operator>>(message<T> &msg, DataType &data) {
            static_assert(std::is_standard_layout<DataType>::value, "Cannot serialize the data");
            size_t i = msg.body.size() - sizeof(DataType);
            std::memcpy(&data, msg.body.data() + i, sizeof(DataType));
            msg.body.resize(i);
            msg.header.size = msg.size();
            return msg;
        }
    };

    template<typename T>
    class Connection;

    template<typename T>
    struct messageDest {
        std::shared_ptr<Connection<T>> _remote = nullptr;
        message<T> _msg;

        friend std::ostream &operator<<(std::ostream &os, const messageDest<T> &msg) {
            os << msg.msg;
            return os;
        }

    };
}

#endif //MYDISCORD_NETWORKMESSAGE_H
