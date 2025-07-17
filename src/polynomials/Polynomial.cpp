#include "Polynomial.h"
#include <iostream>
#include <cassert>

Polynomial::Polynomial() : m_coeffs(1, Complex(0, 0)) {}

// Initialize from coefficients vector
Polynomial::Polynomial(const std::vector<Complex>& coeffs) : m_coeffs(coeffs) {
    trim();
}

Polynomial::Polynomial(std::vector<Complex>&& coeffs) : m_coeffs(std::move(coeffs)) {
    trim();
}

int Polynomial::degree() const {
    return static_cast<int>(m_coeffs.size()) - 1;
}

int Polynomial::size() const {
    return static_cast<int>(m_coeffs.size());
}

void Polynomial::resize(int newSize) {
    m_coeffs.resize(newSize, Complex(0,0));
}

void Polynomial::trim() {
    // Remove trailing zeros (coefficients with zero magnitude) from highest degree terms
    while (m_coeffs.size() > 1 && m_coeffs.back() == 0) {
        m_coeffs.pop_back();
    }
}

Complex Polynomial::evaluate(const Complex& x) const {
    Complex result(0, 0);
    Complex powerOfX = 1;

    for (const auto& coeff : m_coeffs) {
        result += coeff * powerOfX;
        powerOfX *= x;
    }
    return result;
}

const Complex& Polynomial::operator[](int index) const {
    return m_coeffs[index];
}

Complex& Polynomial::operator[](int index) {
    assert(index >= 0 && index < m_coeffs.size());
    return m_coeffs[index];
}

Polynomial &Polynomial::operator+=(const Polynomial &other)
{
    int otherSize = other.size();
    if (otherSize > size()) {
        resize(other.size());
    }
    for (int i = 0; i < otherSize; ++i) {
        (*this)[i] += other[i];
    }
    trim();
    return *this;
}

Polynomial Polynomial::operator+(const Polynomial &other) const
{
    Polynomial result = *this;
    return result += other;
}

Polynomial &Polynomial::operator-=(const Polynomial &other)
{
    int otherSize = other.size();
    if (otherSize > size()) {
        resize(other.size());
    }
    for (int i = 0; i < otherSize; ++i) {
        (*this)[i] -= other[i];
    }
    trim();
    return *this;
}

Polynomial Polynomial::operator-(const Polynomial& other) const {
    Polynomial result = *this;
    return result -= other;
}

Polynomial& Polynomial::operator*=(double scalar)
{
    for (int i = 0; i < size(); ++i) {
        (*this)[i] *= scalar;
    }
    trim();
    return *this;
}

Polynomial Polynomial::operator*(double scalar) const {
    Polynomial result = *this;
    return result *= scalar;
}

Polynomial& Polynomial::operator/=(double scalar)
{
    for (int i = 0; i < size(); ++i) {
        (*this)[i] /= scalar;
    }
    trim();
    return *this;
}

Polynomial Polynomial::operator/(double scalar) const {
    Polynomial result = *this;
    return result /= scalar;
}

Polynomial Polynomial::operator*(const Polynomial& other) const {
    int newSize = this->size() + other.size() - 1;
    std::vector<Complex> resultCoeffs(newSize, Complex(0, 0));

    for (int i = 0; i < this->size(); ++i) {
        for (int j = 0; j < other.size(); ++j) {
            resultCoeffs[i + j] = resultCoeffs[i + j] + ((*this)[i] * other[j]);
        }
    }

    Polynomial result(resultCoeffs);
    result.trim();
    return result;
}

void Polynomial::print() const {
    bool first = true;
    for (int i = degree(); i >= 0; --i) {
        if (!first) std::cout << " + ";
        std::cout << "(" << m_coeffs[i] << ")";
        if (i > 0) std::cout << "x^" << i;
        first = false;
    }
    std::cout << std::endl;
}
