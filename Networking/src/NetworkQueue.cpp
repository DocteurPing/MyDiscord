//
// Created by drping on 6/24/23.
//

#include "../include/NetworkQueue.h"

template<typename T>
const T &Network::ThreadSafeQueue<T>::front() {
    std::scoped_lock lock(muxQueue);
    return deqQueue.front();
}

template<typename T>
const T &Network::ThreadSafeQueue<T>::back() {
    std::scoped_lock lock(muxQueue);
    return deqQueue.back();
}

template<typename T>
void Network::ThreadSafeQueue<T>::push_back(T &item) {
    std::scoped_lock lock(muxQueue);
    deqQueue.push_back(std::move(item));
}

template<typename T>
void Network::ThreadSafeQueue<T>::push_front(T &item) {
    std::scoped_lock lock(muxQueue);
    deqQueue.push_front(std::move(item));
}

template<typename T>
void Network::ThreadSafeQueue<T>::empty() {
    std::scoped_lock lock(muxQueue);
    deqQueue.empty();
}

template<typename T>
void Network::ThreadSafeQueue<T>::count() {
    std::scoped_lock lock(muxQueue);
    return deqQueue.size();
}

template<typename T>
void Network::ThreadSafeQueue<T>::clear() {
    std::scoped_lock lock(muxQueue);
    deqQueue.clear();
}

template<typename T>
T Network::ThreadSafeQueue<T>::pop_front() {
    std::scoped_lock lock(muxQueue);
    T front = std::move(deqQueue.front());
    deqQueue.pop_front();
    return front;
}

template<typename T>
T Network::ThreadSafeQueue<T>::pop_back() {
    std::scoped_lock lock(muxQueue);
    T back = std::move(deqQueue.back());
    deqQueue.pop_back();
    return back;
}