#include <bits/stdc++.h>
using namespace std;
long long gcd(long long a, long long b)
{
    while (b)
    {
        a %= b;
        swap(a, b);
    }
    return a;
}
// modular exponentiation
long long modexp(long long base, long long exp, long long mod)
{
    long long res = 1;
    base %= mod;
    while (exp > 0)
    {
        if (exp % 2 == 1)
            res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

int main()
{
    long long p = 11;
    long long q = 13;
    long long n = p * q;
    long long phi_n = (p - 1) * (q - 1);
    cout << "n = " << n << endl;
    cout << "phi(n) = " << phi_n << endl;
    long long e = 7;
    while (e < phi_n)
    {
        if (gcd(e, phi_n) == 1)
            break;
        e++;
    }
    cout << "Public exponent (e) = " << e << endl;
    long long d;
    for (long long k = 0;; k++)
    {
        if ((1 + k * phi_n) % e == 0)
        {
            d = (1 + k * phi_n) / e;
            break;
        }
    }
    cout << "Private exponent (d) = " << d << endl;
    long long m = 9; // message
    cout << "\nOriginal Message: " << m << endl;
    long long c = modexp(m, e, n);
    cout << "Encrypted Message: " << c << endl;
    long long decrypted = modexp(c, d, n);
    cout << "Decrypted Message: " << decrypted << endl;

    if (m == decrypted)
        cout << "\n Decryption successful!" << endl;
    else
        cout << "\n Decryption failed!" << endl;

    return 0;
}
