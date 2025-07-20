#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include "../utils/utils.h"

class Complex {
public:
    explicit Complex(double real = 0, double imag = 0);
    Complex(double real); // Implicit conversion from double

    Complex(const Complex& other) = default; // Copy Constructor
    Complex& operator=(const Complex& other) = default;

    Complex& operator+=(const Complex& other);
    Complex operator+(const Complex& other) const;
    Complex& operator-=(const Complex& other);
    Complex operator-(const Complex& other) const;

    Complex& operator*=(const Complex& other);
    Complex operator*(const Complex& other) const;
    Complex& operator*=(double scalar);
    Complex operator*(double scalar) const;

    Complex& operator/=(double scalar);
    Complex operator/(double scalar) const;
    Complex& operator/=(const Complex& other);
    Complex operator/(const Complex& other) const;

    bool operator==(const Complex& other) const {
        return equalsWithTolerance(other, Utils::EPSILON);
    }

    double magnitude() const;
    double Re() const;
    double Im() const;
    Complex conjugate() const;

    static Complex fromPolar(double magnitude, double angle);
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
    friend Complex operator*(double scalar, const Complex& z) {
        return z * scalar;
    }
    friend Complex operator/(double scalar, const Complex& z) {
        Complex result = 1;
        result *= scalar;
        return result / z;
    }

    static std::vector<Complex> realToComplex(const std::vector<double>& values);
    static std::pair<std::vector<double>,std::vector<double>> complexToReal(const std::vector<Complex>& values);
private:
    double m_real, m_imaginary;

    bool equalsWithTolerance(const Complex& other, double tolerance) const {
        return std::abs(Re() - other.Re()) < tolerance && std::abs(Im() - other.Im()) < tolerance;
    }
};

#endif // COMPLEX_H
