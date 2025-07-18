#include "utils.h"

bool Utils::is_power_of(int n, int base)
{
    int x = 1;
    while (n > x) {
        x *= base;
    }
    return (x == n);
}

double Utils::round_d_digits(double num, int d)
{
    double factor = std::pow(10.0, d);
    return std::round(num * factor) / factor;
}
