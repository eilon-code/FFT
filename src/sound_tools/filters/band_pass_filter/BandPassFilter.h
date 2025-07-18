#ifndef BANDPASSFILTER_H
#define BANDPASSFILTER_H

#include "../Filter.h"

class BandPassFilter : public Filter {
    int lowCutoff;
    int highCutoff;
public:
    BandPassFilter(int low, int high)
        : lowCutoff(low), highCutoff(high) {}

    bool filter(int freq, int N) const override {
        int absFreq = std::abs(freq);
        return absFreq >= lowCutoff && absFreq <= highCutoff;
    }

    Complex passedFilter(const Complex& freqComponent, int freq, int N) const override {
        return freqComponent;  // No change
    }

    Complex rejected(const Complex& freqComponent, int freq, int N) const override {
        return Complex(0, 0);  // Zero out rejected
    }
};

#endif // BANDPASSFILTER_H
