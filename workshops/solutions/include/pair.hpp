#pragma once
#ifndef PAIR_HPP
#define PAIR_HPP

namespace template_pair {

template <typename T1, typename T2>
class Pair
{
public:
    Pair(T1 first, T2 second) : first_{first}, second_{second} {}

    [[nodiscard]] const T1& first() const { return first_; }
    [[nodiscard]] T1& first() { return first_; }

    [[nodiscard]] const T2& second() const { return second_; }
    [[nodiscard]] T2& second() { return second_; }

private:
    T1 first_;
    T2 second_;
};


template <typename T1>
class Pair<T1, unsigned short>
{
public:
    Pair(T1 first, unsigned short second) : first_{first}, second_{second * 4u} {}

    [[nodiscard]] const T1& first() const { return first_; }
    [[nodiscard]] T1& first() { return first_; }

    [[nodiscard]] unsigned short second() const
    {
        return static_cast<unsigned short>(second_ / 4u);
    }

private:
    T1 first_;
    unsigned second_;
};

template <typename T2>
class Pair<unsigned short, T2>
{
public:
    Pair(unsigned short first, T2 second) : first_{first * 4u}, second_{second} {}

    [[nodiscard]] unsigned short first() const
    {
        return static_cast<unsigned short>(first_ / 4u);
    }

    [[nodiscard]] const T2& second() const { return second_; }
    [[nodiscard]] T2& second() { return second_; }

private:
    unsigned first_;
    T2 second_;
};


template <>
class Pair<unsigned short, unsigned short>
{
public:
    Pair(unsigned short first, unsigned short second)
        : first_{first * 4u}, second_{second * 4u}
    {}

    [[nodiscard]] unsigned short first() const
    {
        return static_cast<unsigned short>(first_ / 4u);
    }
    
    [[nodiscard]] unsigned short second() const
    {
        return static_cast<unsigned short>(second_ / 4u);
    }

private:
    unsigned first_;
    unsigned second_;
};

} // namespace template_pair

#endif // PAIR_HPP