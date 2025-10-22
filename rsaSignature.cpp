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
    // Step 1: Choose two prime numbers
    long long p = 61;
    long long q = 53;
    // Step 2: Compute n and phi(n)
    long long n = p * q;
    long long phi_n = (p - 1) * (q - 1);
    // Step 3: Choose e (public exponent)
    long long e = 17; // সাধারণত 65537 নেওয়া হয়, কিন্তু এখানে ছোট মান
    // Step 4: Compute d (private key)
    long long d;
    for (long long k = 1;; k++)
    {
        if ((1 + k * phi_n) % e == 0)
        {
            d = (1 + k * phi_n) / e;
            break;
        }
    }

    cout << "Public key (e, n): (" << e << ", " << n << ")\n";
    cout << "Private key (d, n): (" << d << ", " << n << ")\n";
    // Step 5: Message (as integer)
    long long message = 42;
    cout << "\nOriginal Message: " << message << endl;
    // Step 6: Signature generation -> S = M^d mod n
    long long signature = modexp(message, d, n);
    cout << "Generated Signature: " << signature << endl;
    // Step 7: Verification -> M' = S^e mod n
    long long verified = modexp(signature, e, n);
    cout << "Verified Message: " << verified << endl;

    if (verified == message)
        cout << "\n Signature Verified Successfully!\n";
    else
        cout << "\n Verification Failed!\n";
    return 0;
}
