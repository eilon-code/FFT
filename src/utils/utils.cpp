#include "utils.h"

bool Utils::isPowerOf(int n, int base)
{
    int x = 1;
    while (n > x) {
        x *= base;
    }
    return (x == n);
}

double Utils::roundToPrecision(double num, int d)
{
    double factor = std::pow(10.0, d);
    return std::round(num * factor) / factor;
}
