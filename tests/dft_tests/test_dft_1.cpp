#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include "FFT.h"           // Contains your DFT/IDFT logic
#include "Complex.h"
#include "Polynomial.h"

const double EPS = 1e-6;

bool approxEqual(const Complex& a, const Complex& b, double tol = EPS) {
    return (a - b).magnitude() < tol;
}

bool approxEqualVec(const std::vector<Complex>& a, const std::vector<Complex>& b, double tol = EPS) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); ++i) {
        if (!approxEqual(a[i], b[i], tol)) return false;
    }
    return true;
}

void testImpulse() {
    std::vector<Complex> input = {1, 0, 0, 0}; // Impulse
    auto output = FFT::dft(input);
    for (auto& val : output) {
        assert(approxEqual(val, Complex(1, 0)));
    }
    std::cout << "✅ Impulse DFT test passed.\n";
}

void testConstant() {
    std::vector<Complex> input = {2, 2, 2, 2}; // Constant
    auto output = FFT::dft(input);
    assert(approxEqual(output[0], Complex(8, 0)));
    for (size_t i = 1; i < output.size(); ++i) {
        assert(approxEqual(output[i], Complex(0, 0)));
    }
    std::cout << "✅ Constant DFT test passed.\n";
}

void testInverseDFT() {
    std::vector<Complex> input = {1, 2, 3, 4};
    auto freq = FFT::dft(input);
    auto output = FFT::idft(freq);
    for (size_t i = 0; i < input.size(); ++i) {
        assert(approxEqual(input[i], output[i]));
    }
    std::cout << "✅ Round-trip DFT/IDFT test passed.\n";
}

void testLinearity() {
    std::vector<Complex> x = {1, 2, 3, 4};
    std::vector<Complex> y = {4, 3, 2, 1};
    std::vector<Complex> x_plus_y(4);
    for (int i = 0; i < 4; ++i) x_plus_y[i] = x[i] + y[i];

    auto dft_x = FFT::dft(x);
    auto dft_y = FFT::dft(y);
    auto dft_sum = FFT::dft(x_plus_y);

    for (int i = 0; i < 4; ++i) {
        assert(approxEqual(dft_sum[i], dft_x[i] + dft_y[i]));
    }
    std::cout << "✅ Linearity test passed.\n";
}

void testDFTOfSinusoid() {
    const int N = 8;
    const int k = 1; // frequency index
    std::vector<Complex> input(N);
    for (int n = 0; n < N; ++n) {
        double angle = 2 * M_PI * k * n / N;
        input[n] = Complex(cos(angle), sin(angle)); // e^(j*2πkn/N)
    }
    auto output = FFT::dft(input);
    for (int i = 0; i < N; ++i) {
        if (i == k)
            assert(approxEqual(output[i], Complex(N, 0)));
        else
            assert(approxEqual(output[i], Complex(0, 0)));
    }
    std::cout << "✅ Complex sinusoid DFT test passed.\n";
}

int main() {
    testImpulse();
    testConstant();
    testInverseDFT();
    testLinearity();
    testDFTOfSinusoid();
    std::cout << "All DFT tests passed ✅✅✅\n";
    return 0;
}
