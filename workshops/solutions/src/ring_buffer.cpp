#include "ring_buffer.hpp"

bool ring_buffer::RingBuffer::empty() const { return buffer_.empty(); }

void ring_buffer::RingBuffer::put(int n)
{
    buffer_.push_back(n);
    while (std::ssize(buffer_) > capacity_) {
        buffer_.pop_front();
    }
}

int ring_buffer::RingBuffer::get()
{
    const int result{buffer_.front()};
    buffer_.pop_front();
    return result;
}
