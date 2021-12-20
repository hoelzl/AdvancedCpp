#pragma once
#ifndef POINTERS_POINTERS_HPP
#define POINTERS_POINTERS_HPP

namespace pointers {

class shape // NOLINT(cppcoreguidelines-special-member-functions)
{
public:
    virtual ~shape() = default;
    virtual void draw() const = 0;
};

class circle final : public shape
{
public:
    circle()
        : circle{0.0, 0.0}
    {}

    circle(double x, double y)
        : x_{x}
        , y_{y}
    {}

    void draw() const override;

    [[nodiscard]] double x() const { return x_; }
    [[nodiscard]] double y() const { return y_; }

private:
    double x_;
    double y_;
};

} // namespace pointers

#endif // POINTERS_POINTERS_HPP
