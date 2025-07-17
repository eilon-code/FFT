#ifndef FFT_H
#define FFT_H

#include <vector>
#include <complex_numbers/Complex.h>
#include <polynomials/Polynomial.h>
#include <cmath>

namespace FFT {
    std::vector<Complex> fft(const Polynomial& A, int n);
    Polynomial ifft(const std::vector<Complex>& values);
    std::vector<Complex> recursive_fft(const Polynomial &A, int n, Complex& unitRoot);
    Polynomial multiplyPolynomials(const Polynomial& A, const Polynomial& B);
}

#endif // FFT_H
