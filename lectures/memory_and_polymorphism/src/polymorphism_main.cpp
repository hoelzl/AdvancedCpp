// ReSharper disable CppClangTidyCppcoreguidelinesOwningMemory
// ReSharper disable CppClangTidyCppcoreguidelinesMacroUsage
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdelete-abstract-non-virtual-dtor"
#endif

#define SHOW_ANIMAL_INSTANCE_LIFE_CYCLE 0
#define OMIT_VIRTUAL_DESTRUCTOR 0

#include "animal.hpp"
#include "cat.hpp"
#include "dog.hpp"

#include <iostream>
#include <memory>
#include <string>

void describe_animal(const Animal* animal)
{
    std::cout << "\n";
    std::cout << animal->describe() << "\n";
    std::cout << animal->make_sound() << "\n";
    std::cout << animal->provide_detailed_description() << "\n";
}

int main()
{
    {
        std::cout << "Dog fluffy{} ================================================\n";
        const Dog fluffy{};
        describe_animal(&fluffy);
    }

    {
        std::cout << "\nCat garfield{} ==============================================\n";
        const Cat garfield{};
        describe_animal(&garfield);
    }

    {
        std::cout << "\nAnimal* animal{new Dog} =====================================\n";
        const Animal* animal{new Dog};
        describe_animal(animal);
        delete animal;

        std::cout << "\nanimal = new Cat ============================================\n";
        animal = new Cat;
        describe_animal(animal);
        delete animal;
    }

    {
        std::cout << "\nstd::unique_ptr<Animal> smart_animal{std::make_unique<Dog>()}\n";
        std::unique_ptr<Animal> smart_animal{std::make_unique<Dog>()};
        describe_animal(smart_animal.get());

        std::cout << "\nsmart_animal = std::make_unique<Cat>() ======================\n";
        smart_animal = std::make_unique<Cat>();
        describe_animal(smart_animal.get());
    }
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif
