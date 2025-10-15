#include <iostream>
using namespace std;

struct Point
{
    int x, y;
    bool infinity;
};

// --- Modulo function ---
int mod(int a, int p)
{
    int r = a % p;
    if (r < 0)
        r += p;
    return r;
}

// --- Extended Euclidean Algorithm ---
int gcdExtended(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int g = gcdExtended(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// --- Modular inverse ---
int modInverse(int a, int p)
{
    int x, y;
    int g = gcdExtended(a, p, x, y);
    if (g != 1)
        throw runtime_error("No inverse exists");
    return (x % p + p) % p;
}

// --- Point addition on elliptic curve ---
Point addPoints(Point P, Point Q, int a, int p)
{
    if (P.infinity)
        return Q;
    if (Q.infinity)
        return P;
    if (P.x == Q.x && mod(P.y + Q.y, p) == 0)
        return {0, 0, true}; // P == -Q

    int s;
    if (P.x == Q.x && P.y == Q.y)
    {
        // Point doubling
        int num = mod(3 * P.x * P.x + a, p);
        int den = modInverse(2 * P.y, p);
        s = mod(num * den, p);
    }
    else
    {
        // Point addition
        int num = mod(Q.y - P.y, p);
        int den = modInverse(mod(Q.x - P.x, p), p);
        s = mod(num * den, p);
    }

    int xr = mod(s * s - P.x - Q.x, p);
    int yr = mod(s * (P.x - xr) - P.y, p);

    return {xr, yr, false};
}

// --- Point negation ---
Point negatePoints(Point P, int p)
{
    if (P.infinity)
        return P;
    return {P.x, mod(-P.y, p), false};
}

// --- Point subtraction ---
Point subtract(Point P, Point Q, int a, int p)
{
    return addPoints(P, negatePoints(Q, p), a, p);
}

// --- Scalar multiplication (k * P) ---
Point scalarMultiply(Point P, int k, int a, int p)
{
    Point R = {0, 0, true}; // infinity point
    Point temp = P;

    while (k > 0)
    {
        if (k & 1)
            R = addPoints(R, temp, a, p);
        temp = addPoints(temp, temp, a, p);
        k >>= 1;
    }

    return R;
}

// --- Ciphertext structure ---
struct Ciphertext
{
    Point C1;
    Point C2;
};

// --- Encryption ---
Ciphertext encrypt(Point M, Point G, Point Q, int k, int a, int p)
{
    Point C1 = scalarMultiply(G, k, a, p);
    Point kQ = scalarMultiply(Q, k, a, p);
    Point C2 = addPoints(M, kQ, a, p);
    return {C1, C2};
}

// --- Decryption ---
Point decrypt(Ciphertext ct, int d, int a, int p)
{
    Point dC1 = scalarMultiply(ct.C1, d, a, p);
    return subtract(ct.C2, dC1, a, p);
}

// --- Main function ---
int main()
{
    int p = 97, a = 2, b = 2;
    Point G = {5, 1, false};

    cout << "Curve: y^2 = x^3 + 2x + 2 (mod 97)\n";
    cout << "Base point G = (" << G.x << "," << G.y << ")\n";

    // Bob's private key
    int d = 7;
    Point Q = scalarMultiply(G, d, a, p); // Bob's public key

    cout << "Bob's public key Q = (" << Q.x << "," << Q.y << ")\n";

    // Message point
    Point M = {6, 3, false};
    cout << "Message point M = (" << M.x << "," << M.y << ")\n";

    // Alice's random key
    int k = 5;
    Ciphertext ct = encrypt(M, G, Q, k, a, p);

    cout << "\nCiphertext:\n";
    cout << "C1 = (" << ct.C1.x << "," << ct.C1.y << ")\n";
    cout << "C2 = (" << ct.C2.x << "," << ct.C2.y << ")\n";

    // Bob decrypts
    Point decrypted = decrypt(ct, d, a, p);
    cout << "\nDecrypted point M' = (" << decrypted.x << "," << decrypted.y << ")\n";

    if (decrypted.x == M.x && decrypted.y == M.y)
        cout << " Decryption successful\n";
    else
        cout << "Decryption failed\n";

    return 0;
}
