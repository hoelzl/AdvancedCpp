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

#endif // RING_BUFFER_HPP