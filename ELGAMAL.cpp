
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

// Function to calculate (base^exponent) % modulus efficiently
long long int power(long long int base, long long int exponent, long long int modulus) {
    long long int result = 1;
    base %= modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

// Function to perform modular inverse
long long int modInverse(long long int n, long long int modulus) {
    n = n % modulus;
    for (int x = 1; x < modulus; x++) {
        if ((n * x) % modulus == 1) {
            return x;
        }
    }
    return 1;
}

// Fermat's Little Theorem:

// long long int modInverse(long long int n, long long int modulus) {
//     return power(n, modulus - 2, modulus);
// }


int main() {
    // Seeding the random number generator
    srand(time(0));

    // Publicly known prime and primitive root
    long long int p = 1000000007;
    long long int d = 5;

    cout << "Public Prime (p): " << p << std::endl;
    cout << "Public Primitive Root (d): " << d << std::endl;

    // Key Generation
    long long int e1 = rand() % (p - 2) + 1; // Private key for receiver
    long long int e2 = power( e1,d, p);      // Public key for receiver

    cout << "\nReceiver's Private Key (e1): " << e1 << std::endl;
    cout << "Receiver's Public Key (e2): " << e2 << std::endl;

    // Encryption
    long long int M; // Message to be encrypted
    cin>>M;
    cout << "\nOriginal Message (M): " << M << std::endl;

    long long int R = rand() % (p - 2) + 1; // Random integer for sender
    long long int c1 = power(e1, R, p);
    long long int c2 = (power(e2, R, p) * M) % p;

    cout << "Ciphertext (c1, c2): (" << c1 << ", " << c2 << ")" << std::endl;

    // Decryption
    long long int s = power(c1, d, p);
    long long int s_inverse = modInverse(s, p);
    long long int decrypted_M = (c2 * s_inverse) % p;

    cout << "\nDecrypted Message: " << decrypted_M << std::endl;

    return 0;
}