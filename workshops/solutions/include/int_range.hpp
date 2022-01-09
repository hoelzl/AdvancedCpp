#pragma once
#ifndef INT_RANGE_HPP
#define INT_RANGE_HPP
#include <stdexcept>
#include <vector>

namespace stl {

class IntRangeV0
{
private:
    std::vector<int> numbers_{};

public:
    using iterator = decltype(numbers_)::iterator;

    IntRangeV0(int min, int max)
    {
        if (min > max) {
            throw std::invalid_argument("min must be <= max.");
        }
        for (int i{min}; i <= max; ++i) {
            numbers_.push_back(i);
        }
    }

    iterator begin() { return numbers_.begin(); }
    iterator end() { return numbers_.end(); }
};

void run_int_range_v0_example();


class IntRange
{
public:
    class IntRangeIterator
    {
    public:
        explicit IntRangeIterator(int value) : value_{value} {}
        const int& operator*() { return value_; }
        const int& operator*() const { return value_; }

        IntRangeIterator& operator++()
        {
            ++value_;
            return *this;
        }

        IntRangeIterator operator++(int)
        {
            const auto old{*this};
            operator++();
            return old;
        }

        bool operator==(const IntRangeIterator& rhs) const
        {
            return value_ == rhs.value_;
        }

    private:
        int value_;
    };

    using iterator = IntRangeIterator;

    IntRange(int min, int max) : min_{min}, max_{max}
    {
        if (min > max) {
            throw std::invalid_argument("min must be <= max.");
        }
    }

    [[nodiscard]] iterator begin() const { return IntRangeIterator{min_}; }
    [[nodiscard]] iterator end() const { return IntRangeIterator{max_ + 1}; }

private:
    int min_;
    int max_;
};

} // namespace stl

#endif // INT_RANGE_HPP