#pragma once

#include <random>
#include "coordinate.hpp"

class Random {
public:
    static std::minstd_rand rnd;
    static std::uniform_real_distribution<double> uniform_dist_0_1;
    static std::normal_distribution<double> normal_dist_0_1;

    static double get_normal();
    static double get_uniform();
    static double get_uniform_neg_pos();
    
    static Vec3f get_normal_vec();
    static Vec3f get_uniform_vec();
};
