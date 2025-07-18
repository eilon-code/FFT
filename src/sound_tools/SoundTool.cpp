#include "SoundTool.h"

Polynomial SoundTool::samplesToPolynomial(const std::vector<double> &samples) {
    std::vector<Complex> coeffs(samples.size());
    for (size_t i = 0; i < samples.size(); ++i) {
        coeffs[i] = Complex(samples[i], 0);
    }
    return Polynomial(coeffs);
}

std::vector<double> SoundTool::polynomialToSamples(const Polynomial &poly) {
    std::vector<double> samples(poly.size());
    for (int i = 0; i < poly.size(); ++i) {
        samples[i] = poly[i].Re();
    }
    return samples;
}
