#include <cmath>
#include "Complex.h"

Complex::Complex(double real, double imag) : m_real(real), m_imaginary(imag) {}
Complex::Complex(double real) : m_real(real), m_imaginary(0.0) {}

Complex& Complex::operator+=(const Complex &other)
{
    m_real += other.Re();
    m_imaginary += other.Im();
    return *this;
}

Complex Complex::operator+(const Complex& other) const {
    Complex result = *this;
    return result += other;
}

Complex& Complex::operator-=(const Complex &other)
{
    m_real -= other.Re();
    m_imaginary -= other.Im();
    return *this;
}

Complex Complex::operator-(const Complex& other) const {
    Complex result = *this;
    return result -= other;
}

Complex& Complex::operator*=(const Complex &other)
{
    double x = Re();
    double y = Im();
    m_real = x * other.Re() - y * other.Im();
    m_imaginary = x * other.Im() + y * other.Re();
    return *this;
}

Complex Complex::operator*(const Complex& other) const {
    Complex result = *this;
    return result *= other;
}

Complex& Complex::operator*=(double scalar)
{
    m_real *= scalar;
    m_imaginary *= scalar;
    return *this;
}

Complex Complex::operator*(double scalar) const {
    return Complex(m_real * scalar, m_imaginary * scalar);
}

Complex &Complex::operator/=(double scalar)
{
    m_real /= scalar;
    m_imaginary /= scalar;
    return *this;
}

Complex Complex::operator/(double scalar) const
{
    Complex result = *this;
    return result /= scalar;
}

Complex &Complex::operator/=(const Complex &other)
{
    double mag = other.magnitude();
    (*this) *= other.conjugate();
    (*this) /= (mag * mag);
    return *this;
}

Complex Complex::operator/(const Complex &other) const
{
    Complex result = *this;
    return result /= other;
}

double Complex::magnitude() const {
    double x = Re();
    double y = Im();
    return std::sqrt(x * x + y * y);
}

double Complex::Re() const {
    return m_real;
}

double Complex::Im() const {
    return m_imaginary;
}

Complex Complex::conjugate() const {
    return Complex(Re(), -Im());
}

Complex Complex::fromPolar(double magnitude, double angle) {
    return Complex(magnitude * std::cos(angle), magnitude * std::sin(angle));
}

std::ostream& operator<<(std::ostream& os, const Complex& c) {
    double x = Utils::roundToPrecision(c.Re(), 2);
    double y = Utils::roundToPrecision(c.Im(), 2);
    if (std::abs(x) < Utils::EPSILON)
        os << x;
    else if (std::abs(x) < Utils::EPSILON)
        os << y << "i";
    else
        os << x << (y >= 0 ? " + " : " - ") << std::abs(y) << "i";
    return os;
}


std::vector<Complex> Complex::realToComplex(const std::vector<double> &values)
{
    std::vector<Complex> result;
    result.reserve(values.size());
    for (auto& val : values) {
        result.emplace_back(val, 0.0);
    }
    return result;
}

std::pair<std::vector<double>, std::vector<double>> Complex::complexToReal(const std::vector<Complex> &values)
{
    std::pair<std::vector<double>, std::vector<double>> result;
    result.first.reserve(values.size());
    result.second.reserve(values.size());
    for (auto& c : values) {
        result.first.push_back(c.Re());
        result.second.push_back(c.Im());
    }
    return result;
}
