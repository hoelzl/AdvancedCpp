#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-abstract-non-virtual-dtor"
#endif

#define OMIT_VIRTUAL_DESTRUCTOR 1
#define SHOW_ANIMAL_INSTANCE_LIFE_CYCLE 1

#include "animal.h"
#include "cat.h"
#include "dog.h"

#include <iostream>
#include <memory>
#include <string>

void describe_animal(const Animal* animal)
{
    std::cout << "Describing an animal.\n";
    std::cout << animal->describe() << std::endl;
    std::cout << animal->make_sound() << std::endl;
    std::cout << animal->provide_detailed_description() << std::endl;
}

int main()
{
    std::cout << "Dog fluffy{} ================================================"
              << std::endl;
    Dog fluffy{};
    std::cout << fluffy.describe() << std::endl;
    std::cout << fluffy.make_sound() << std::endl;
    std::cout << fluffy.provide_detailed_description() << std::endl;

    std::cout << "Cat garfield{} =============================================="
              << std::endl;
    Cat garfield{};
    std::cout << garfield.describe() << std::endl;
    std::cout << garfield.make_sound() << std::endl;
    std::cout << garfield.provide_detailed_description() << std::endl;

    std::cout << "Animal* animal{new Dog} ====================================="
              << std::endl;
    Animal* animal{new Dog};
    describe_animal(animal);
    delete animal;

    std::cout << "animal = new Cat ============================================"
              << std::endl;
    animal = new Cat;
    describe_animal(animal);
    delete animal;

    std::cout << "std::unique_ptr<Animal> smart_animal{std::make_unique<Dog>()}"
              << std::endl;
    std::unique_ptr<Animal> smart_animal{std::make_unique<Dog>()};
    describe_animal(smart_animal.get());

    std::cout << "smart_animal = std::make_unique<Cat>() ======================"
              << std::endl;
    smart_animal = std::make_unique<Cat>();
    describe_animal(smart_animal.get());
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
