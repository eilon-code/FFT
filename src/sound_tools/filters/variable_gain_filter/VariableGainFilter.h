#ifndef VARIABLEGAINFILTER_H
#define VARIABLEGAINFILTER_H

#include "../Filter.h"
#include <cmath>
#include <functional>

class VariableGainFilter : public Filter {
    std::function<double(int)> gainFunction;  // gain as function of abs(freq)

public:
    explicit VariableGainFilter(std::function<double(int)> gainFn)
        : gainFunction(std::move(gainFn)) {}

    bool filter(int freq, int N) const override {
        return true;  // apply gain to all frequencies
    }

    Complex passedFilter(const Complex& freqComponent, int freq, int N) const override {
        // This is never used since we override applyFilter
        return freqComponent * gainFunction(std::abs(freq));
    }

    Complex rejected(const Complex& freqComponent, int freq, int N) const override {
        return Complex(0, 0);
    }
};

#endif // VARIABLEGAINFILTER_H
