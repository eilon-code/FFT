#ifndef SOUND_TOOL_H
#define SOUND_TOOL_H

#include <vector>
#include <complex_numbers/Complex.h>
#include <polynomials/Polynomial.h>
#include <FFT.h>

class SoundTool {
public:
    // Convert raw audio samples (real doubles) to Polynomial of Complex numbers
    // (the values of the samples will become the coefficients to the polynomial.)
    static Polynomial samplesToPolynomial(const std::vector<double>& samples);

    // Convert Polynomial back to real samples (discard imaginary part)
    static std::vector<double> polynomialToSamples(const Polynomial& poly);

    // Perform FFT on samples (pad size to power of two)
    // (Encode the sound samples to phazor for each frequency)
    static std::vector<Complex> performFFT(const std::vector<double>& samples) {
        Polynomial poly = samplesToPolynomial(samples);
        int n = 1;
        while (n <= poly.degree()) n <<= 1; // next power of two
        return FFT::fft(poly, n);
    }

    // Perform IFFT to get time domain samples from frequency domain
    // (Decode the sound samples from the phazors for each frequency)
    static std::vector<double> performIFFT(const std::vector<Complex>& freqComponents) {
        Polynomial poly = FFT::ifft(freqComponents);
        return polynomialToSamples(poly);
    }
};

#endif // SOUND_TOOL_H
