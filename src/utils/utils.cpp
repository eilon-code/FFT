#include "utils.h"

bool Utils::isPowerOf(int n, int base)
{
    return n == ceilPowerOf(n, base);
}

int Utils::ceilPowerOf(int lowerBound, int base)
{
    int x = 1;
    while (lowerBound > x) {
        x *= base;
    }
    return x;
}

double Utils::roundToPrecision(double num, int d)
{
    double factor = std::pow(10.0, d);
    return std::round(num * factor) / factor;
}
