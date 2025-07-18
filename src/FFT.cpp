#include <cassert>
#include "FFT.h"
#include "../utils/utils.h"

std::vector<Complex> FFT::fft(const Polynomial &A, int n) {
    assert(n > A.degree() && Utils::is_power_of(n,2));
    Polynomial padded = A;
    padded.resize(n); // zero padding
    Complex omega = Complex::fromPolar(1, 2 * Utils::PI / n);

    // the FFT results the vector result:
    //  
    //  /  1  z_0^1      z_0^2      ...    z_0^{n-1}    \           /  a_0     \           /  v_0      \ 
    //  |  1  z_1^1      z_1^2      ...    z_1^{n-1}    |           |  a_1     |           |  v_1      | 
    //  |  1  z_2^1      z_2^2      ...    z_2^{n-1}    |   *. .*   |  a_2     |           |  v_2      | 
    //  |  .    .          .      .           .         |    .*.    |   .      |   =====   |   .       | 
    //  |  .    .          .         .        .         |   *   *   |   .      |   =====   |   .       | 
    //  |  .    .          .            .     .         |           |   .      |           |   .       | 
    //  \  1  z_{n-1}^1  z_{n-1}^2  ...  z_{n-1}^{n-1}  /           \  a_{n-1} /           \  v_{n-1}  / 
    //
    //
    // for the values:
    // z_j = omega^j
    // a_j = coefficient j of the polynomial A
    //
    // in other words, FFT computes:
    // forall j, v_j = A(z_j) by order.
    return recursive_fft(padded, n, omega);
}

std::vector<Complex> FFT::recursive_fft(const Polynomial &A, int n, Complex &unitRoot) {
    if (n == 1) {
        return { A.size() > 0 ? A[0] : Complex(0, 0) }; // 1 = n > deg(A))  -->  A(x) = a_0
    }

    Polynomial A_even, A_odd;
    A_even.resize(n/2);
    A_odd.resize(n/2);
    for (int i = 0; i < n; ++i) {
        Complex val = i < A.size() ? A[i] : 0;
        if (i % 2 == 0) A_even[i / 2] = val;
        else A_odd[i / 2] = val;
    }
    // under the notation below:
    // A(x) =       a_0 + a_1 * x + a_2 * x^2 + a_3 * x^3 + ...
    
    // we get:
    // A_even(t) =  a_0 + a_2 * t + a_4 * t^2 + a_6 * t^3 + ...
    // A_odd(t) =   a_1 + a_3 * t + a_5 * t^2 + a_7 * t^3 + ...

    // and thus:
    // A(x) = A_even(t=x^2) + x * A_odd(t=x^2)

    Complex t = unitRoot * unitRoot;
    std::vector<Complex> fft_even = recursive_fft(A_even, n / 2, t);
    std::vector<Complex> fft_odd = recursive_fft(A_odd, n / 2, t);

    std::vector<Complex> result(n);
    Complex x = 1;
    for (int i = 0; i < n / 2; ++i) {
        result[i] = fft_even[i] + x * fft_odd[i];
        result[i + n / 2] = fft_even[i] - x * fft_odd[i];
        x *= unitRoot;
    }
    return result;
}

Polynomial FFT::ifft(const std::vector<Complex> &values) {
    // the Inverse-FFT results the vector result:
    //  
    //  /  1  z_0^1      z_0^2      ...    z_0^{n-1}    \ -1        /  v_0     \           /  r_0      \ 
    //  |  1  z_1^1      z_1^2      ...    z_1^{n-1}    |           |  v_1     |           |  r_1      | 
    //  |  1  z_2^1      z_2^2      ...    z_2^{n-1}    |   *. .*   |  v_2     |           |  r_2      | 
    //  |  .    .          .      .           .         |    .*.    |   .      |   =====   |   .       | 
    //  |  .    .          .         .        .         |   *   *   |   .      |   =====   |   .       | 
    //  |  .    .          .            .     .         |           |   .      |           |   .       | 
    //  \  1  z_{n-1}^1  z_{n-1}^2  ...  z_{n-1}^{n-1}  /           \  v_{n-1} /           \  r_{n-1}  / 
    //
    //
    // for the values:
    // z_j = omega^j (where omega = e^{2 * PI / n})
    // v_j = A(z_j)   (the input for the algorithm)
    //
    // in other words, IFFT computes:
    // forall j, r_j = coefficient a_j of the polynomial A.
    // and returns the polynomial A(x).


    // Luckily, the inverse matrix is given to be:
    //
    //  /  1  z_0^1      z_0^2      ...    z_0^{n-1}    \ -1                 /  1  w_0^1      w_0^2      ...    w_0^{n-1}    \ 
    //  |  1  z_1^1      z_1^2      ...    z_1^{n-1}    |                    |  1  w_1^1      w_1^2      ...    w_1^{n-1}    | 
    //  |  1  z_2^1      z_2^2      ...    z_2^{n-1}    |              1     |  1  w_2^1      w_2^2      ...    w_2^{n-1}    | 
    //  |  .    .          .      .           .         |    =====    --- *  |  .    .          .      .           .         | 
    //  |  .    .          .         .        .         |    =====     n     |  .    .          .         .        .         | 
    //  |  .    .          .            .     .         |                    |  .    .          .            .     .         | 
    //  \  1  z_{n-1}^1  z_{n-1}^2  ...  z_{n-1}^{n-1}  /                    \  1  w_{n-1}^1  w_{n-1}^2  ...  w_{n-1}^{n-1}  / 
    //
    //
    // under the notation w_j = {omega.conjucture()}^j

    // now, the result should be:
    //
    //         /  1  w_0^1      w_0^2      ...    w_0^{n-1}    \           /  v_0     \           /  r_0      \ 
    //         |  1  w_1^1      w_1^2      ...    w_1^{n-1}    |           |  v_1     |           |  r_1      | 
    //   1     |  1  w_2^1      w_2^2      ...    w_2^{n-1}    |   *. .*   |  v_2     |           |  r_2      | 
    //  --- *  |  .    .          .      .           .         |    .*.    |   .      |   =====   |   .       | 
    //   n     |  .    .          .         .        .         |   *   *   |   .      |   =====   |   .       | 
    //         |  .    .          .            .     .         |           |   .      |           |   .       | 
    //         \  1  w_{n-1}^1  w_{n-1}^2  ...  w_{n-1}^{n-1}  /           \  v_{n-1} /           \  r_{n-1}  / 

    // now the similiarity to the FFT calculation is obvious. (omega.conjucture() is a unit root as well as omega)

    // so, we will generate a polynomial with coefficients v_0, v_1, ..., v_{n-1}
    // and call it V(x) = v_0 + v_1 * x + ... + v_{n-1} * x^{n-1}
    // then we will use the 'recursive_fft' to evaluate the matrix multiplication above
    // we will assign a result polynomial A with the coefficients of the result vector
    // at last we will divide the polynomial A by scalar n and result the polynomial with coefficients r_0, r_1, ..., r_{n-1}


    int n = values.size();
    assert(Utils::is_power_of(n,2));
    Polynomial V(values);

    Complex omega = Complex::fromPolar(1, 2 * Utils::PI / n);
    Complex omegaConjugate = omega.conjugate();
    std::vector<Complex> result = recursive_fft(V, n, omegaConjugate);
    Polynomial A = Polynomial(result);
    A /= n * 1.0;
    A.trim();
    return A;
}

Polynomial FFT::multiplyPolynomials(const Polynomial &A, const Polynomial &B)
{
    int d = A.degree() + B.degree(); // the degree of the multiplication polynomial C(x) = A(x) * B(x)
    int n = 1;
    while (n <= d) {
        n *= 2;
    }
    std::vector<Complex> A_values = fft(A, n); // A(x) for x = omega_n^0, ..., omega_n^{n-1}
    std::vector<Complex> B_values = fft(B, n); // B(x) for x = omega_n^0, ..., omega_n^{n-1}

    std::vector<Complex> C_values(n);
    for (int i = 0; i < n; ++i) {
        C_values[i] = A_values[i] * B_values[i]; // C(x) = A(x) * B(x), for each x mentioned above
    }
    return ifft(C_values);
}
