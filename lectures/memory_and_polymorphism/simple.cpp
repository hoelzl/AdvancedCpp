#include <iostream>

struct Base {
    Base(int x, int y, int z) : x{x}, y{y}, z{z}
    {
    }
    virtual ~Base() = default;
    [[nodiscard]] virtual int get_sum() const
    {
        return x + y + z;
    }

protected:
    int x;
    int y;

private:
    int z;
};

struct Derived : public Base {
    Derived(int x, int y, int z) : Base{x, y, z}
    {
    }
    [[nodiscard]] int get_sum() const override
    {
        return Base::get_sum() + 1;
    }
    [[nodiscard]] int get_product() const
    {
        return x * y;
    }
};

void print_it(const Base& base)
{
    std::cout << "Printing: " << base.get_sum() << std::endl;
}

int main()
{
    Base base{2, 3, 5};
    std::cout << "base: " << base.get_sum() << std::endl;
    print_it(base);

    Derived derived{2, 3, 5};
    std::cout << "derived: " << derived.get_sum() << ", "
              << derived.get_product() << std::endl;
    print_it(derived);

    Base* base_pointer{&base};
    std::cout << "base_pointer: " << base_pointer->get_sum() << std::endl;

    base_pointer = &derived;
    std::cout << "base_pointer: " << base_pointer->get_sum() << std::endl;

    base = derived; // NOLINT(cppcoreguidelines-slicing)
    std::cout << "base: " << base.get_sum() << std::endl;
}
