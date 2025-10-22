#include <bits/stdc++.h>
using namespace std;

long long modexp(long long base, long long exp, long long mod)
{
    base = base % mod;
    long long res = 1;
    while (exp > 0)
    {
        if (exp % 2 == 1)
            res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

long long  modInverse(long long  n, long long  modulus)
{
    n = n % modulus;
    for (long long x = 1; x < modulus; x++)
    {
        if ((n * x) % modulus == 1)
        {
            return x;
        }
    }
    return 1;
}

int main()
{
    
    long long p = 11;                     // prime number
    long long alpha = 2;                  // primitive root
    long long a = 3;                      // private key
    long long beta = modexp(alpha, a, p); // public key component
    cout << "Public key: {p=" << p << ", alpha=" << alpha << ", beta=" << beta << "}\n";
    cout << "Private key: a=" << a << "\n\n";
    long long m = 11; // message
    long long k = 3; // random k coprime with p-1 (gcd(k,p-1)=1)
    long long y1 = modexp(alpha, k, p);
    long long k_inv = modInverse(k, p - 1); // inverse of k modulo (p-1)

    long long temp = (m - (a * y1) % (p - 1)) % (p - 1);
    if (temp < 0)
        temp += (p - 1);
    long long y2 = (temp * k_inv) % (p - 1);

    cout << "Message: " << m << endl;
    cout << "Random k: " << k << endl;
    cout << "Signature: (y1=" << y1 << ", y2=" << y2 << ")\n\n";

    // ----- Verification -----
    long long v1 = (modexp(beta, y1, p) * modexp(y1, y2, p)) % p;
    long long v2 = modexp(alpha, m, p);

    cout << "Verification left side = " << v1 << endl;
    cout << "Verification right side = " << v2 << endl;

    if (v1 == v2)
        cout << "\n Signature is VALID\n";
    else
        cout << "\n Signature is INVALID\n";

    return 0;
}
