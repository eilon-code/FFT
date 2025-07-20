#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <cmath>

namespace Utils {
    static constexpr double EPSILON = 1e-9; // computation tolerance
    static const double PI = std::acos(-1);

    bool isPowerOf(int n, int base);
    int ceilPowerOf(int lowerBound, int base);
    double roundToPrecision(double num, int d);
}

#endif // UTILS_H
