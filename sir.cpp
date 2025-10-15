#include <iostream>
 
using namespace std;
 
struct Point { int x, y; bool infinity; };
 
// Simple modulo operation
int mod(int a, int p) {
    int r = a % p;
    if (r < 0) r += p;
    return r;
}
 
// Returns gcd(a,b) and sets x such that a*x ≡ 1 mod p
int gcdExtended(int a, int b, int &x, int &y) {
    if (b == 0) {
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
 
// Modular inverse using recursive EEA
int modInverse(int a, int p) {
    int x, y;
    int g = gcdExtended(a, p, x, y);
    if (g != 1) throw runtime_error("No inverse exists");
    return (x % p + p) % p; // ensure positive
}
 
// Add two points on curve: y^2 = x^3 + ax + b (mod p)
Point addPoints(Point P, Point Q, int a, int p) {
 
    if (P.infinity) return Q;
 
    if (Q.infinity) return P;
 
    if (P.x == Q.x && mod(P.y + Q.y, p) == 0) return {0, 0, true}; // P == -Q
 
    int s;
 
    if (P.x == Q.x && P.y == Q.y) {
        // point doubling
        int num = mod(3 * P.x * P.x + a, p);
        int den = modInverse(2 * P.y, p);
        s = mod(num * den, p);
    } else {
        // point addition
        int num = mod(Q.y - P.y, p);
        int den = modInverse(mod(Q.x - P.x, p), p);
        s = mod(num * den, p);
    }
 
    int xr = mod(s*s - P.x - Q.x, p);
    int yr = mod(s*(P.x - xr) - P.y, p);
 
    return {xr, yr, false};
}
 
 
 
// Negate a point
Point negatePoints(Point P, int p) {
    if (P.infinity) return P;
    return {P.x, mod(-P.y, p), false};
}
 
// Subtract points
Point subtract(Point P, Point Q, int a, int p) {
    return addPoints(P, negatePoints(Q, p), a, p);
}
 
// Scalar multiplication k*P (very basic)
Point scalarMultiply() {
 
}
 
// ----------- ECC Encryption/Decryption ----------
struct Ciphertext { Point C1; Point C2; };
 
Ciphertext encrypt() {
    // TODO
    // Calculate C1 and C2
 
    return {C1, C2};
}
 
Point decrypt() {
    // TODO
    // Calculate C2 - dC1
 
    return subtract(ct.C2, dC1, a, p);
}
 
int main() {
    // Curve: y^2 = x^3 + ax + b (mod p)
    int p = 97, a = 2, b = 2;
    Point G = {5, 1, false};  // base point
 
    cout << "Curve: y^2 = x^3 + 2x + 2 (mod 97)\n";
    cout << "Base point G = (" << G.x << "," << G.y << ")\n";
 
    // Bob's key
    int d = 7; // private key
 
    // TODO
    Point Q = scalarMultiply(); // public key
 
    cout << "Bob's public key PB = (" << Q.x << "," << Q.y << ")\n";
 
    // Message as a point
    Point M = {6, 3, false};
    cout << "Message point M = (" << M.x << "," << M.y << ")\n";
 
    // Alice encrypts
    int k = 5; // ephemeral key
 
    // TODO
    Ciphertext ct = encrypt();
 
    cout << "Ciphertext:" << endl;
    cout << "C1 = (" << ct.C1.x << "," << ct.C1.y << ")\n";
    cout << "C2 = (" << ct.C2.x << "," << ct.C2.y << ")\n";
 
    // Bob decrypts
    // TODO
    Point decrypted = decrypt(ct, d, a, p);
    cout << "Decrypted M' = (" << decrypted.x << "," << decrypted.y << ")\n";
 
    if (decrypted.x == M.x && decrypted.y == M.y)
        cout << "Decryption successful\n";
    else
        cout << "Decryption failed\n";
 
    return 0;
}