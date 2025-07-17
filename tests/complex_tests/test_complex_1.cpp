#include <cassert>
#include "../../src/complex_numbers/Complex.h"

void test_basic_operations() {
    Complex a(3, 4);
    Complex b(1, -1);

    assert((a + b) == Complex(4, 3));
    assert((a - b) == Complex(2, 5));
    assert((a * b) == Complex(7, 1));
    assert((a / 2.0) == Complex(1.5, 2.0));
    assert((a.conjugate()) == Complex(3, -4));
}

void test_equality() {
    Complex a(1.0000000001, 2.0000000001);
    Complex b(1.0000000002, 2.0000000002);
    assert(a == b); // Within EPSILON
}

int main() {
    test_basic_operations();
    test_equality();
    std::cout << "All Complex tests passed!\n";
    return 0;
}
