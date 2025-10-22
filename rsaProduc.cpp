// RSA Product Cipher Demonstration
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll gcd(ll a, ll b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
// Fast modular exponentiation
ll powMod(ll base, ll exp, ll n)
{
    ll res = 1;
    base %= n;
    while (exp > 0)
    {
        if (exp & 1)
            res = (res * base) % n;
        exp >>= 1;
        base = (base * base) % n;
    }
    return res;
}

int main()
{
    // Step 1: Choose primes
    ll p = 11;
    ll q = 13;

    // Step 2: Compute n and φ(n)
    ll n = p * q;
    ll phi = (p - 1) * (q - 1);

    // Step 3: Choose e
    ll e = 2;
    while (gcd(e, phi) != 1)
        e++;

    // Step 4: Compute private key d
    long long d;
    for (long long k = 0;; k++)
    {
        if ((1 + k * phi) % e == 0)
        {
            d = (1 + k * phi) / e;
            break;
        }
    }
    cout << "Private exponent (d) = " << d << endl;

    // Step 5: Display keys
    cout << "RSA Product Cipher\n";
    cout << "-----------------------\n";
    cout << "p = " << p << ", q = " << q << endl;
    cout << "n = " << n << ", phi(n) = " << phi << endl;
    cout << "Public key (e, n): (" << e << ", " << n << ")\n";
    cout << "Private key (d, n): (" << d << ", " << n << ")\n\n";

    // Step 6: Two plaintext messages
    ll ms1 = 5;
    ll ms2 = 9;
    cout << "Plaintext 1: " << ms1 << endl;
    cout << "Plaintext 2: " << ms2 << endl;

    // Step 7: Encrypt both
    ll c1 = powMod(ms1, e, n);
    ll c2 = powMod(ms2, e, n);
    cout << "\nCipher1 = " << c1 << "\nCipher2 = " << c2 << endl;

    // Step 8: Product of plaintexts (mod n)
    ll product_plain = (ms1 * ms2) % n;
    cout << "\nProduct of Plaintexts (ms1 * ms2 mod n) = " << product_plain << endl;

    // Step 9: Product of ciphertexts (Homomorphic property)
    ll c = (c1 * c2) % n;
    cout << "Product Ciphertext (c1 * c2 mod n) = " << c << endl;

    // Step 10: Decrypt the product cipher
    ll dec = powMod(c, d, n);
    cout << "Decrypted Product Message = " << dec << endl;

    // Step 11: Check Homomorphic property
    if (dec == product_plain)
        cout << "\n✅ Homomorphic Property Verified! (Decrypted = Product of plaintexts)\n";
    else
        cout << "\n❌ Property Failed!\n";

    return 0;
}
