#ifndef BANDSTOPFILTER_H
#define BANDSTOPFILTER_H

#include "../Filter.h"

class BandStopFilter : public Filter {
    int lowCutoff;
    int highCutoff;
public:
    BandStopFilter(int low, int high)
        : lowCutoff(low), highCutoff(high) {}

    bool filter(int freq, int N) const override {
        int absFreq = std::abs(freq);
        return absFreq < lowCutoff || absFreq > highCutoff;
    }

    Complex passedFilter(const Complex& freqComponent, int freq, int N) const override {
        return freqComponent;  // Keep as is
    }

    Complex rejected(const Complex& freqComponent, int freq, int N) const override {
        return Complex(0, 0);  // Zero rejected frequencies
    }
};

#endif // BANDSTOPFILTER_H
