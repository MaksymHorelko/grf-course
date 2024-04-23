#include <iostream>
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

ZZ ModExp(const ZZ& a, const ZZ& b, const ZZ& p) {
    ZZ result;
    PowerMod(result, a, b, p);
    return result;
}

bool IsPrime(const ZZ& n) {
    return ProbPrime(n, 10);
}

ZZ GenerateRandomPrime(int num_bits) {
    ZZ prime;
    GenPrime(prime, num_bits);
    return prime;
}

int main() {
    ZZ factor_base;
    factor_base = RandomBits_ZZ(50);

    ZZ p;
    do {
        p = (power2_ZZ(4096) + 1) * factor_base + 1;
        factor_base += 2;
    } while (!IsPrime(p));

    ZZ g;
    g = RandomBits_ZZ(10);

    cout << "Згенеровані параметри:" << endl;
    cout << "p: " << p << endl;
    cout << "g: " << g << endl;

    return 0;
}
