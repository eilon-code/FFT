#ifndef NOTCHFILTER_H
#define NOTCHFILTER_H

#include "../Filter.h"

class NotchFilter : public Filter {
    int notchFreq;
public:
    NotchFilter(int freq) : notchFreq(freq) {}

    bool filter(int freq, int N) const override {
        return freq != notchFreq;
    }

    Complex passedFilter(const Complex& freqComponent, int freq, int N) const override {
        return freqComponent;
    }

    Complex rejected(const Complex& freqComponent, int freq, int N) const override {
        return Complex(0, 0);
    }
};

#endif // NOTCHFILTER_H
