#ifndef HIGHPASSFILTER_H
#define HIGHPASSFILTER_H

#include "../Filter.h"

class HighPassFilter : public Filter {
    int cutoff;
public:
    HighPassFilter(int cutoffFrequency) : cutoff(cutoffFrequency) {}

    bool filter(int freq, int N) const override {
        return std::abs(freq) >= cutoff;
    }

    Complex passedFilter(const Complex& freqComponent, int freq, int N) const override {
        return freqComponent; // No change
    }

    Complex rejected(const Complex& freqComponent, int freq, int N) const override {
        return Complex(0, 0); // Zero out rejected frequencies
    }
};

#endif // HIGHPASSFILTER_H
