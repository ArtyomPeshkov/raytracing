#include "randomiser.hpp"

std::minstd_rand Random::rnd;
std::uniform_real_distribution<double> Random::uniform_dist_0_1 = std::uniform_real_distribution<double>(0.0, 1.0);
std::normal_distribution<double> Random::normal_dist_0_1 = std::normal_distribution<double>(0.0, 1.0);

