#include "SoundTool.h"

Polynomial SoundTools::samplesToPolynomial(const std::vector<double> &samples) {
    std::vector<Complex> coeffs(samples.size());
    for (size_t i = 0; i < samples.size(); ++i) {
        coeffs[i] = Complex(samples[i], 0);
    }
    return Polynomial(coeffs);
}

std::vector<double> SoundTools::polynomialToSamples(const Polynomial &poly) {
    std::vector<double> samples(poly.size());
    for (int i = 0; i < poly.size(); ++i) {
        samples[i] = poly[i].Re();
    }
    return samples;
}

std::vector<Complex> SoundTools::frequencyBandPassFilter(const std::vector<Complex> &freqComponents, int low, int high) {
    std::vector<Complex> filtered = freqComponents;
    for (int i = 0; i < (int)freqComponents.size(); ++i) {
        if (i < low || i > high) {
            filtered[i] = Complex(0, 0);
        }
    }
    return filtered;
}
