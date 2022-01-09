#pragma once

#include "animal.h"
#include <string>

using namespace std::string_literals;

class Cat : public Animal
{
#if SHOW_ANIMAL_INSTANCE_LIFE_CYCLE
public:
    Cat() noexcept
    {
        std::cout << "Creating cat instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this)
                  << " via default constructor." << std::endl;
    }
    Cat(const Cat& cat) : Animal(cat)
    {
        std::cout << "Creating cat instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this)
                  << " via copy constructor." << std::endl;
    }

    Cat(Cat&& cat) noexcept : Animal(std::move(cat))
    {
        std::cout << "Creating cat instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this)
                  << " via move constructor." << std::endl;
    }

    Cat& operator=(const Cat& cat)
    {
        Animal::operator=(cat);
        std::cout << "Copy assigning cat instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this) << "." << std::endl;
        return *this;
    }

    Cat& operator=(Cat&& cat) noexcept
    {
        Animal::operator=(std::move(cat));
        std::cout << "Move assigning cat instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this) << "." << std::endl;
        return *this;
    }

    ~Cat()
    {
        std::cout << "Destroying cat instance " << std::hex
                  << reinterpret_cast<std::uintptr_t>(this) << "." << std::endl;
    }
#endif

protected:
    [[nodiscard]] std::string describe_impl() const override
    {
        return "A cat. The most elegant and majestic of animals."s;
    }

    [[nodiscard]] std::string make_sound_impl() const override
    {
        return "[Meow]!"s;
    }

    [[nodiscard]] std::string provide_detailed_description_impl() const override
    {
        return "The glorious species of cats.\n"s +
               "No description can do this animal justice.\n"s +
               "So don't even try.\n"s;
    }
};
