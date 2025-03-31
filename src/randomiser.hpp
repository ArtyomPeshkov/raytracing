#pragma once

#include <random>

class Random {
public:
    static std::minstd_rand rnd;
    static std::uniform_real_distribution<double> uniform_dist_0_1;
    static std::normal_distribution<double> normal_dist_0_1;
};
