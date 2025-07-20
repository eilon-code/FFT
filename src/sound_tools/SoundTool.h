#ifndef SOUND_TOOL_H
#define SOUND_TOOL_H

#include <vector>
#include <complex_numbers/Complex.h>
#include <polynomials/Polynomial.h>
#include <FFT.h>

namespace SoundTool {
    // Perform DFT to get frequency domain from time domain samples
    // (Encode the sound samples to the phazors for each frequency)
    std::vector<Complex> computeFrequencySpectrum(const std::vector<double>& samples) {
        std::vector<Complex> complexSamples = Complex::realToComplex(samples);
        return FFT::dft(complexSamples);
    }

    // Perform IDFT to get time domain samples from frequency domain
    // (Decode the sound samples from the phazors for each frequency)
    std::vector<double> reconstructSignalFromSpectrum(const std::vector<Complex>& freqComponents) {
        std::vector<Complex> complexSamples = FFT::idft(freqComponents);
        auto result = Complex::complexToReal(complexSamples);
        for (double im : result.second) {
            if (std::abs(im) > Utils::EPSILON) {
                std::cerr << "Warning: significant imaginary component in reconstructed signal.\n";
                break;
            }
        }
        return result.first; // dismiss the imaginary parts
    }
};

#endif // SOUND_TOOL_H
