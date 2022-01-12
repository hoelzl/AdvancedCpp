#pragma once
#ifndef RING_BUFFER_HPP
#define RING_BUFFER_HPP
#include <deque>

namespace ring_buffer {

class RingBuffer
{
public:
    explicit RingBuffer(int capacity) : capacity_{capacity} {}

    [[nodiscard]] bool empty() const;
    void put(int n);
    int get();

private:
    int capacity_;
    std::deque<int> buffer_{};
};

} // namespace ring_buffer


namespace generic_ring_buffer {

template <typename T>
class RingBuffer
{
public:
    explicit RingBuffer(int capacity) : capacity_{capacity} {}

    [[nodiscard]] bool empty() const;
    void put(T n);
    T get();

private:
    int capacity_;
    std::deque<T> buffer_{};
};

template <typename T>
bool RingBuffer<T>::empty() const
{
    return buffer_.empty();
}

template <typename T>
void RingBuffer<T>::put(T n)
{
    buffer_.push_back(n);
    while (std::ssize(buffer_) > capacity_) {
        buffer_.pop_front();
    }
}
template <typename T>
T RingBuffer<T>::get()
{
    const T result{buffer_.front()};
    buffer_.pop_front();
    return result;
}

} // namespace generic_ring_buffer


#endif // RING_BUFFER_HPP