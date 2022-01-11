// Created by Dr. Matthias Hölzl on 17/05/2021.
// Copyright (c) 2021 Dr. Matthias Hölzl. See file LICENSE.md.

// ReSharper disable CppClangTidyBugproneExceptionEscape
// ReSharper disable CppUseAuto
// ReSharper disable CppClangTidyClangDiagnosticUnusedMacros
// ReSharper disable CppClangTidyCppcoreguidelinesMacroUsage

#define SHOW_ANIMAL_INSTANCE_LIFE_CYCLE 1
#define OMIT_VIRTUAL_DESTRUCTOR 1

#include "cat.hpp"
#include "dog.hpp"
#include <iostream>

int main()
{
    std::cout << "\nDog fluffy{} ==========================================\n";
    const Dog fluffy{};
    std::cout << "\nDog dolly{Dog{}} ======================================\n";
    Dog dolly{Dog{}};
    std::cout << "\nDog pepper{fluffy} ====================================\n";
    Dog pepper{fluffy}; // NOLINT(performance-unnecessary-copy-initialization)
    std::cout << "\nDog pebbles{std::move(pepper)} ========================\n";
    Dog pebbles{std::move(pepper)};

    std::cout << "\ndolly = fluffy ========================================\n";
    dolly = fluffy;
    std::cout << "\ndolly = std::move(pebbles) ============================\n";
    dolly = std::move(pebbles);

    std::cout << "\nCat loki{} ============================================\n";
    Cat loki{};
    std::cout << "\nCat dexter{loki} ======================================\n";
    Cat dexter{loki}; // NOLINT(performance-unnecessary-copy-initialization)
    std::cout << "\nCat thor{std::move(dexter)} ===========================\n";
    Cat thor{std::move(dexter)};

    std::cout << "\ndexter = loki =========================================\n";
    dexter = loki;
    std::cout << "\nthor = std::move(loki) ================================\n";
    thor = std::move(loki);
    std::cout << "\n";
    return 0;
}
