#pragma once

#include <random>

std::mt19937 mersenne;

namespace utility {
    int random(int a, int b) {
        std::uniform_int_distribution<> rng{a, b};
        return rng(mersenne);
    }
}