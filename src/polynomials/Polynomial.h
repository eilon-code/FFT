#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <complex_numbers/Complex.h>

class Polynomial;

namespace FFT {
    Polynomial multiplyPolynomials(const Polynomial&, const Polynomial&);
}

class Polynomial {
public:
    Polynomial(); // Zero polynomial
    Polynomial(const std::vector<Complex>& coeffs); // Initialize from coefficients
    Polynomial(std::vector<Complex>&& coeffs); // direct references (no copy of coefficients)

    Polynomial(const Polynomial& other) = default;
    Polynomial& operator=(const Polynomial& other) = default;

    int degree() const;
    int size() const;
    void resize(int newSize);
    void trim(); // Remove trailing zeros

    Complex evaluate(const Complex& x) const; // at single point (Complexity of O(n))

    const Complex& operator[](int index) const;
    Complex& operator[](int index);

    Polynomial& operator+=(const Polynomial& other);
    Polynomial operator+(const Polynomial& other) const;
    Polynomial& operator-=(const Polynomial& other);
    Polynomial operator-(const Polynomial& other) const;

    Polynomial& operator*=(double scalar);
    Polynomial operator*(double scalar) const;
    Polynomial& operator/=(double scalar);
    Polynomial operator/(double scalar) const;

    Polynomial operator*(const Polynomial& other) const;
    void print() const;
private:
    std::vector<Complex> m_coeffs; // Coefficients, m_coeffs[i] is x^i
};

#endif // POLYNOMIAL_H
