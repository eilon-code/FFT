#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

class Complex {
public:
    explicit Complex(double real = 0, double imag = 0);
    Complex(double real); // Implicit conversion from double
    Complex(const Complex&) = default; // Copy Constructor

    Complex(const Complex& other) = default;
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

    static constexpr double EPSILON = 1e-9;

    bool operator==(const Complex& other) const {
        return equalsWithTolerance(other, EPSILON);
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
private:
    double m_real, m_imaginary;

    bool equalsWithTolerance(const Complex& other, double tolerance) const {
        return std::abs(Re() - other.Re()) < tolerance && std::abs(Im() - other.Im()) < tolerance;
    }
};

#endif // COMPLEX_H
