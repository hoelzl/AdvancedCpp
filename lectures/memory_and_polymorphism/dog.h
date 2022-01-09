#pragma once

#include "animal.h"
#include <string>

using namespace std::string_literals;

class Dog : public Animal
{
#if SHOW_ANIMAL_INSTANCE_LIFE_CYCLE
public:
    Dog() noexcept
    {
        std::cout << "Creating dog instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this)
                  << " via default constructor." << std::endl;
    }

    Dog(const Dog& dog)
    {
        std::cout << "Creating dog instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this)
                  << " via copy constructor." << std::endl;
    }

    Dog(Dog&& dog) noexcept
    {
        std::cout << "Creating dog instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this)
                  << " via move constructor." << std::endl;
    }

    Dog& operator=(const Dog& dog)
    {
        Animal::operator=(dog);
        std::cout << "Copy assigning dog instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this) << "." << std::endl;
        return *this;
    }

    Dog& operator=(Dog&& dog) noexcept
    {
        Animal::operator=(dog);
        std::cout << "Move assigning dog instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this) << "." << std::endl;
        return *this;
    }

    ~Dog()
    {
        std::cout << "Destroying dog instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this) << "." << std::endl;
    }
#endif

protected:
    [[nodiscard]] std::string describe_impl() const override
    {
        return "A dog. What is there to say?"s;
    }

    [[nodiscard]] std::string make_sound_impl() const override
    {
        return "[Woof]!"s;
    }
};
