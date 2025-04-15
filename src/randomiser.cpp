#include "randomiser.hpp"

std::minstd_rand Random::rnd;
std::uniform_real_distribution<double> Random::uniform_dist_0_1 = std::uniform_real_distribution<double>(0.0, 1.0);
std::normal_distribution<double> Random::normal_dist_0_1 = std::normal_distribution<double>(0.0, 1.0);

double Random::get_normal() {
    return normal_dist_0_1(rnd);
};

double Random::get_uniform() {
    return uniform_dist_0_1(rnd);
};

double Random::get_uniform_neg_pos() {
    return 2 * uniform_dist_0_1(rnd) - 1;
};

Vec3f Random::get_normal_vec() {
    return Vec3f(get_normal(), get_normal(), get_normal());
};

Vec3f Random::get_uniform_vec() {
    return Vec3f(get_uniform(), get_uniform(), get_uniform());
};