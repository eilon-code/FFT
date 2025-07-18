#ifndef FILTER_H
#define FILTER_H

#include <vector>
#include "../../complex_numbers/Complex.h"

class Filter {
public:
    virtual ~Filter() = default;

    virtual bool filter(int freq, int N) const = 0;
    virtual Complex passedFilter(const Complex& freqComponent, int freq, int N) const = 0;
    virtual Complex rejected(const Complex& freqComponent, int freq, int N) const = 0;

    // Applies the filter to a vector of frequency-domain samples
    virtual std::vector<Complex> applyFilter(const std::vector<Complex>& freqComponents) const final {
        int N = freqComponents.size();
        std::vector<Complex> result(N);
        for (int i = 0; i < N; ++i) {
            int freq = (i <= N / 2) ? i : -(N - i);  // Negative frequencies
            if (filter(freq, N))
                result[i] = passedFilter(freqComponents[i], i, N);
            else
                result[i] = rejected(freqComponents[i], i, N);
        }
        return result;
    }
};

#endif // FILTER_H