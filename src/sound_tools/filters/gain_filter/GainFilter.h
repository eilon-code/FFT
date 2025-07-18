#ifndef GAINFILTER_H
#define GAINFILTER_H

#include "../Filter.h"

class GainFilter : public Filter {
    int cutoff;
    double gain;
public:
    GainFilter(int cutoffFrequency, double gainFactor)
        : cutoff(cutoffFrequency), gain(gainFactor) {}

    bool filter(int freq, int N) const override {
        return std::abs(freq) <= cutoff;
    }

    Complex passedFilter(const Complex& freqComponent, int freq, int N) const override {
        return freqComponent * gain;
    }

    Complex rejected(const Complex& freqComponent, int freq, int N) const override {
        return Complex(0, 0);  // Remove rejected frequencies
    }
};

#endif // GAINFILTER_H
