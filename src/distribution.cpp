#include "randomiser.hpp"
#include "distribution.hpp"

Vec3f Cosine::sample(Vec3f x, Vec3f n) {
    Vec3f dir = Random::get_normal_vec().normalized() + n;
    double len = sqrt(dir.self_dot());

    if (len <= 1e-7 || dir * n <= 1e-7) {
        return n;
    }

    return 1.0 / len * dir;
}

double Cosine::pdf(Vec3f x, Vec3f n, Vec3f d) {
    return std::max(0.0, d * n / double(acos(-1)));
}

double Light::pdf(Vec3f x, Vec3f n, Vec3f d) {
    auto maybeInter = primitive.intersection(Ray(x, d));
    if (!maybeInter.has_value()) {
        return 0.0;
    }

    auto firstInter = maybeInter.value();
    double ans = getPDF(x, d, x + firstInter.t * d, firstInter.normal);

    maybeInter = primitive.intersection(Ray(x + (firstInter.t + 0.0001) * d, d));
    if (!maybeInter.has_value()) {
        return ans;
    }

    auto secondInter = maybeInter.value();
    return ans + getPDF(x, d, x + (firstInter.t + secondInter.t + 0.0001) * d, secondInter.normal);
}

Vec3f Light::sample(Vec3f x, Vec3f n) {
    if (primitive.type == PrimitiveType::BOX) {
        return boxSample(x, n);
    } else {
        return ellipsoidSample(x, n);
    }
}

Vec3f Light::boxSample(Vec3f x, Vec3f n) {
    double d_x = primitive.data.x;
    double d_y = primitive.data.y;
    double d_z = primitive.data.z;

    double w_x = d_y * d_z;
    double w_y = d_x * d_z;
    double w_z = d_x * d_y;

    while (true) {
        double u = Random::get_uniform() * (w_x + w_y + w_z);
        double sign = Random::get_uniform() > 0.5 ? 1 : -1;
        Vec3f point = Vec3f(Random::get_uniform_neg_pos() * d_x, Random::get_uniform_neg_pos() * d_y, Random::get_uniform_neg_pos() * d_z);

        if (u < w_x) {
            point.x = sign * d_x;
        } else if (u < w_x + w_y) {
            point.y = sign * d_y;
        } else {
            point.z = sign * d_z;
        }

        auto rotated = Quaternion(-1.0 * primitive.rotation.v, primitive.rotation.w);

        Vec3f actual = rotated.rotate(point) + primitive.position;
        if (primitive.intersection(Ray(x, (actual - x).normalized())).has_value()) {
            return (actual - x).normalized();
        }
    }
}

Vec3f Light::ellipsoidSample(Vec3f x, Vec3f n) {
    Vec3f r = primitive.data;

    while (true) {
        auto normal = Random::get_normal_vec().normalized();

        Vec3f point = Vec3f(r.x * normal.x, r.y * normal.y, r.z * normal.z);

        auto rotated = Quaternion(-1.0 * primitive.rotation.v, primitive.rotation.w);

        Vec3f actual = rotated.rotate(point) + primitive.position;
        if (primitive.intersection(Ray(x, (actual - x).normalized())).has_value()) {
            return (actual - x).normalized();
        }
    }
}

double Light::getPDF(Vec3f x, Vec3f d, Vec3f y, Vec3f yn) {
    if (primitive.type == PrimitiveType::BOX) {
        return boxgetPDF(x, d, y, yn);
    } else {
        return ellipsoidgetPDF(x, d, y, yn);
    }
}

double Light::boxgetPDF(Vec3f x, Vec3f d, Vec3f y, Vec3f yn) {
    double d_x = primitive.data.x;
    double d_y = primitive.data.y;
    double d_z = primitive.data.z;
    return (x - y).self_dot() / (8 * (d_y * d_z + d_x * d_z + d_x * d_y) * fabs(d * yn));
}


double Light::ellipsoidgetPDF(Vec3f x, Vec3f d, Vec3f y, Vec3f yn) {
    Vec3f r = primitive.data;
    auto transformed = primitive.rotation.rotate(y - primitive.position);

    Vec3f n = Vec3f(transformed.x / r.x, transformed.y / r.y, transformed.z / r.z);
    double prob = 1.0 / (4 * acos(-1) * sqrt(Vec3f{n.x * r.y * r.z, r.x * n.y * r.z, r.x * r.y * n.z}.self_dot()));
    return prob * (x - y).self_dot() / fabs(d * yn);
}


Vec3f Mix::sample(Vec3f x, Vec3f n) {
    int distNum = Random::get_uniform() * components.size();
    return components[distNum].sample(x, n);
}

double Mix::pdf(Vec3f x, Vec3f n, Vec3f d) {
    double ans = 0;
    for (auto& component : components) {
        ans += component.pdf(x, n, d);
    }
    return ans / double(components.size());
}
