// Elgamal Product Cipher
#include <bits/stdc++.h>
using namespace std;

// modular exponentiation: (base^exp) mod mod
long long modexp(long long base,long long exp,long long mod)
{
    long long res=1;
    long long b=base%mod;
    while(exp>0){
        if(exp%2==1){
            res=(res*b)%mod;
        }
        b=(b*b)%mod;
        exp /=2;
    }
    return res;
}

// modular inverse: a^(p-2) mod p (Fermat's little theorem)
long long modinv(long long a, long long p)
{
    return modexp(a, p - 2, p);
}

int main()
{
    long long p = 11;                     // prime
    long long alpha = 2;                  // primitive root
    long long a = 3;                      // private key
    long long beta = modexp(alpha, a, p); // public key component

    cout << "Public key: {p=" << p << ", alpha=" << alpha << ", beta=" << beta << "}\n";
    cout << "Private key: a=" << a << "\n";

    // messages
    long long m1 = 7, m2 = 9;
    // random values (normally random)
    long long k1 = 5, k2 =7;

    // Encrypt m1
    long long y11 = modexp(alpha, k1, p);
    long long y21 = (m1 * modexp(beta, k1, p))%p;

    // Encrypt m2
    long long y12 = modexp(alpha, k2, p);
    long long y22 = (m2 * modexp(beta, k2, p)) % p ;

    cout << "\nCipher1: (" << y11 << "," << y21 << ")\n";
    cout << "Cipher2: (" << y12 << "," << y22 << ")\n";

    // Homomorphic product (component-wise multiply mod p)
    long long Y1 = (y11 * y12) % p;
    long long Y2 = (y21 * y22) % p;
    cout << "\nProduct Cipher: (" << Y1 << "," << Y2 << ")\n";

    // Decrypt both and product
    long long x1 = (y21 * modinv(modexp(y11, a, p), p)) % p;
    long long x2 = (y22 * modinv(modexp(y12, a, p), p)) % p;
    long long xProd = (Y2 * modinv(modexp(Y1, a, p), p)) % p;

    cout << "\nDecrypted m1 = " << x1;
    cout << "\nDecrypted m2 = " << x2;
    cout << "\nDecrypted product = " << xProd;
    cout << "\nExpected (m1*m2 mod p) = " << (m1 * m2) % p << "\n";
}
