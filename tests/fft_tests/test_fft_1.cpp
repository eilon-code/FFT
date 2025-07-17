#include <cassert>
#include "../../src/complex_numbers/Complex.h"
#include "../../src/polynomials/Polynomial.h"
#include "../../src/FFT.h"

void test_fft_multiplication() {
    Polynomial A({1, 2}); // 1 + 2x
    Polynomial B({3, 4}); // 3 + 4x
    Polynomial C = A * B; // Expected: 3 + 10x + 8x^2

    assert(C.size() >= 3);
    assert(C[0] == 3);
    assert(C[1] == 10);
    assert(C[2] == 8);
}

int main() {
    test_fft_multiplication();
    std::cout << "All FFT tests passed!\n";
    return 0;
}
