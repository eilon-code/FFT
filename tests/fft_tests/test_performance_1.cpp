#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <cmath>
#include "polynomials/Polynomial.h"

// Naive polynomial multiplication for correctness check on small cases
Polynomial naiveMultiply(const Polynomial& A, const Polynomial& B) {
    int degreeA = A.degree();
    int degreeB = B.degree();
    std::vector<Complex> resultCoeffs(degreeA + degreeB + 1, Complex(0,0));
    
    for (int i = 0; i <= degreeA; ++i) {
        for (int j = 0; j <= degreeB; ++j) {
            resultCoeffs[i+j] += A[i] * B[j];
        }
    }
    return Polynomial(resultCoeffs);
}

// Generate random polynomial of given degree
Polynomial generateRandomPoly(int degree) {
    std::vector<Complex> coeffs(degree+1);
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<> dist(-10.0, 10.0);
    for (int i = 0; i <= degree; ++i) {
        coeffs[i] = Complex(dist(rng), 0);
    }
    return Polynomial(coeffs);
}

// Check if two polynomials are approximately equal (for small degrees)
bool approxEqual(const Polynomial& A, const Polynomial& B, double tol = 1e-6) {
    int maxDegree = std::max(A.degree(), B.degree());
    for (int i = 0; i <= maxDegree; ++i) {
        Complex diff = A[i] - B[i];
        if (diff.magnitude() > tol) {
            return false;
        }
    }
    return true;
}

double timeLimit(int n) { // semi-linear bound
    double a_0 = 1;
    double c = 0.00004;
    return a_0 + c * n;
}

int main() {
    // Degrees to test (increase sizes exponentially)
    std::vector<int> testDegrees = {10, 100, 1000, 10000, 100000, 1000000};
    
    for (int degree : testDegrees) {
        std::cout << "Testing polynomial multiplication with degree = " << degree << std::endl;
        Polynomial A = generateRandomPoly(degree);
        Polynomial B = generateRandomPoly(degree);
        
        // Time FFT multiply
        auto start = std::chrono::high_resolution_clock::now();
        Polynomial C = A * B;
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        
        std::cout << "FFT multiplication took " << elapsed.count() << " seconds." << std::endl;
        
        if (elapsed.count() > timeLimit(degree)) {
            std::cout << "⚠️  Warning: time limit exceeded!" << std::endl;
        }
        
        // For small sizes, verify correctness vs naive multiply
        if (degree <= 1000) {
            Polynomial C_naive = naiveMultiply(A, B);
            if (approxEqual(C, C_naive)) {
                std::cout << "✅ Correct result (matches naive multiplication)" << std::endl;
            } else {
                std::cout << "❌ Incorrect result (does not match naive multiplication)" << std::endl;
            }
        }
        
        std::cout << "---------------------------------------------" << std::endl;
    }
    
    return 0;
}
