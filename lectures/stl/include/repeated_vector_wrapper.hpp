#pragma once
#ifndef REPEATED_VECTOR_WRAPPER_HPP
#define REPEATED_VECTOR_WRAPPER_HPP
#include <vector>

namespace stl {

template <typename T>
class RepeatedVectorWrapper
{
public:
    class RepeatedVectorIterator
    {
    public:
        friend RepeatedVectorIterator RepeatedVectorWrapper::end();

        RepeatedVectorIterator(
            typename std::vector<T>::iterator begin_it,
            typename std::vector<T>::iterator end_it, int num_iterations)
            : RepeatedVectorIterator{
                std::move(begin_it), std::move(end_it), num_iterations, 1}
        {}

        T& operator*() { return *it_; }
        const T& operator*() const { return *it_; }

        RepeatedVectorIterator& operator++()
        {
            if (it_ + 1 == end_it_) {
                if (current_iteration_ < num_iterations_) {
                    it_ = begin_it_;
                    ++current_iteration_;
                }
                else {
                    it_ = end_it_;
                }
            }
            else {
                ++it_;
            }
            return *this;
        }

        RepeatedVectorIterator operator++(int)
        {
            auto old{*this};
            operator++();
            return old;
        }

        bool operator==(const RepeatedVectorIterator& rhs) const
        {
            return (it_ == rhs.it_) && (current_iteration_ == rhs.current_iteration_);
        }

    private:
        RepeatedVectorIterator(
            typename std::vector<T>::iterator begin_it,
            typename std::vector<T>::iterator end_it, int num_iterations,
            int current_iteration)
            : begin_it_{begin_it}
            , end_it_{end_it}
            , it_{num_iterations >= 0 ? begin_it : end_it}
            , num_iterations_{num_iterations}
            , current_iteration_{current_iteration}
        {}

        typename std::vector<T>::iterator begin_it_;
        typename std::vector<T>::iterator end_it_;
        typename std::vector<T>::iterator it_;
        int num_iterations_;
        int current_iteration_;
    };

    using iterator = RepeatedVectorIterator;
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;

    explicit RepeatedVectorWrapper(std::vector<T>& vec, int num_iterations)
        : vec_{vec}, num_iterations_{num_iterations}
    {}

    iterator begin()
    {
        if (num_iterations_ <= 0 || vec_.empty()) {
            return end();
        }
        return RepeatedVectorIterator{vec_.begin(), vec_.end(), num_iterations_};
    }

    iterator end()
    {
        return RepeatedVectorIterator(
            vec_.end(), vec_.end(), num_iterations_, num_iterations_);
    }

private:
    std::vector<T>& vec_;
    int num_iterations_;
};

} // namespace stl

#endif // REPEATED_VECTOR_WRAPPER_HPP