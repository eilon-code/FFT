#ifndef LOWPASSFILTER_H
#define LOWPASSFILTER_H

#include "../Filter.h"

class LowPassFilter : public Filter {
    int cutoff;
public:
    LowPassFilter(int cutoffFrequency) : cutoff(cutoffFrequency) {}

    bool filter(int freq, int N) const override {
        return std::abs(freq) <= cutoff;
    }

    Complex passedFilter(const Complex& freqComponent, int freq, int N) const override {
        return freqComponent; // No change
    }

    Complex rejected(const Complex& freqComponent, int freq, int N) const override {
        return Complex(0, 0); // Zero out rejected frequencies
    }
};

#endif // LOWPASSFILTER_H
