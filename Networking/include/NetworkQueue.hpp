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

        const T &front() {
            std::scoped_lock lock(muxQueue);
            return deqQueue.front();
        }

        const T &back() {
            std::scoped_lock lock(muxQueue);
            return deqQueue.back();
        }

        void push_back(T &item) {
            std::scoped_lock lock(muxQueue);
            deqQueue.push_back(std::move(item));
        }

        void push_front(T &item) {
            std::scoped_lock lock(muxQueue);
            deqQueue.push_front(std::move(item));
        }

        bool empty() {
            std::scoped_lock lock(muxQueue);
            return deqQueue.empty();
        }

        void count() {
            std::scoped_lock lock(muxQueue);
            return deqQueue.size();
        }

        void clear() {
            std::scoped_lock lock(muxQueue);
            deqQueue.clear();
        }

        T pop_front() {
            std::scoped_lock lock(muxQueue);
            T front = std::move(deqQueue.front());
            deqQueue.pop_front();
            return front;
        }

        T pop_back() {
            std::scoped_lock lock(muxQueue);
            T back = std::move(deqQueue.back());
            deqQueue.pop_back();
            return back;
        }

    protected:
        std::mutex muxQueue;
        std::deque<T> deqQueue;
    };
}

#endif //MYDISCORD_NETWORKQUEUE_H
