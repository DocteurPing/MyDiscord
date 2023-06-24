//
// Created by drping on 6/24/23.
//

#ifndef MYDISCORD_NETWORKQUEUE_H
#define MYDISCORD_NETWORKQUEUE_H

#include <mutex>
#include <deque>

namespace Network {
    template<typename T>
    class ThreadSafeQueue {
    public:
        ThreadSafeQueue() = default;
        ThreadSafeQueue(const ThreadSafeQueue<T> &) = delete;
        ~ThreadSafeQueue() {
            clear();
        }
        const T &front();
        const T &back();
        void push_back(T &item);
        void push_front(T &item);
        void empty();
        void count();
        void clear();
        T pop_front();
        T pop_back();

    protected:
        std::mutex muxQueue;
        std::deque<T> deqQueue;
    };
}

#endif //MYDISCORD_NETWORKQUEUE_H
