#include <cassert>
#include "../../src/complex_numbers/Complex.h"
#include "../../src/polynomials/Polynomial.h"

void test_polynomial_addition() {
    Polynomial A({1, 2, 3}); // 1 + 2x + 3x^2
    Polynomial B({4, 5});    // 4 + 5x
    Polynomial C = A + B;

    assert(C.size() == 3);
    assert(C[0] == 5);
    assert(C[1] == 7);
    assert(C[2] == 3);
}

void test_polynomial_evaluation() {
    Polynomial P({1, 2, 1}); // (x+1)^2
    Complex x = 1;
    assert(P.evaluate(x) == 4);
}

int main() {
    test_polynomial_addition();
    test_polynomial_evaluation();
    std::cout << "All Polynomial tests passed!\n";
    return 0;
}
