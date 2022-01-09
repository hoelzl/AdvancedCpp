// Created by Dr. Matthias Hölzl on 17/05/2021.
// Copyright (c) 2021 Dr. Matthias Hölzl. See file LICENSE.md.

#define SHOW_ANIMAL_INSTANCE_LIFE_CYCLE 1
#include "cat.h"
#include "dog.h"
#include <iostream>

int main()
{
    std::cout << "Dog fluffy{} =================================" << '\n';
    Dog fluffy{};
    std::cout << "Dog dolly{Dog{}} =============================" << '\n';
    Dog dolly{Dog{}};
    std::cout << "Dog pepper{fluffy} ===========================" << '\n';
    Dog pepper{fluffy}; // NOLINT(performance-unnecessary-copy-initialization)
    std::cout << "Dog pebbles{std::move(pepper)} ===============" << '\n';
    Dog pebbles{std::move(pepper)};

    std::cout << "dolly = fluffy ===============================" << '\n';
    dolly = fluffy;
    std::cout << "dolly = std::move(pebbles) ===================" << '\n';
    dolly = std::move(pebbles);

    std::cout << "Cat loki{} ===================================" << '\n';
    Cat loki{};
    std::cout << "Cat dexter{loki} =============================" << '\n';
    Cat dexter{loki}; // NOLINT(performance-unnecessary-copy-initialization)
    std::cout << "Cat thor{std::move(dexter)} ==================" << '\n';
    Cat thor{std::move(dexter)};

    std::cout << "dexter = loki ================================" << '\n';
    dexter = loki;
    std::cout << "thor = std::move(loki) =======================" << '\n';
    thor = std::move(loki);

    return 0;
}
