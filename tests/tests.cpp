#include <iostream>
#include <cassert>
#include "../src/polynomials/Polynomial.h"

int main() {
    Polynomial a({1, 2});
    Polynomial b({3, 4});
    Polynomial c = a * b;
    assert(c[0] == 3);
    assert(c[1] == 10);
    assert(c[2] == 8);
    std::cout << "Polynomial multiplication test passed!" << std::endl;
    return 0;
}
