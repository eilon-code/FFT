#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <cmath>

namespace Utils {
    static constexpr double EPSILON = 1e-9; // computation tolerance
    static const double PI = std::acos(-1);

    bool is_power_of(int n, int base);
    double round_d_digits(double num, int d);
}

#endif // UTILS_H
