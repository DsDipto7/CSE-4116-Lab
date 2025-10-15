#include <iostream>
using namespace std;

unsigned long long int gcd(unsigned long long int a, unsigned long long int b)
{
    while (b)
    {
        a %= b;
        swap(a, b);
    }
    return a;
}

unsigned long long int power(unsigned long long int a, unsigned long long int b, unsigned long long int c)
{
    __uint128_t res = 1;
    __uint128_t aa = a;
    __uint128_t bb = b;
    __uint128_t cc = c;
    aa %= cc;
    while (bb > 0)
    {
        if ((bb % 2) == 1)
        {
            res = (res * aa) % cc;
        }
        aa = (aa * aa) % cc;
        bb /= 2;
    }
    return res;
}

int main()
{

    unsigned long long int p = 100003;
    unsigned long long int q = 100019;

    unsigned long long int n = p * q;
    cout << n << endl;

    unsigned long long int fi_n = (p - 1) * (q - 1);
    cout << fi_n << endl;

    unsigned long long int e = 10000;
    while (e < fi_n)
    {
        if (gcd(e, fi_n) == 1)
        {
            break;
        }
        e++;
    }

    cout << e << endl;

    unsigned long long int d;

    __uint128_t k;

    for (k = 0;; k++)
    {

        if ((1 + k * fi_n) % e == 0)
        {
            d = (1 + k * fi_n) / e;
            break;
        }
    }

    cout << d << endl;

    unsigned long long int m1;
    cin >> m1;
    cout << m1 << endl;

    unsigned long long int c1 = power(m1, e, n);
    cout << c1 << endl;

    unsigned long long int d1 = power(c1, d, n);
    cout << d1 << endl;

    unsigned long long int m2;
    cin >> m2;
    cout << m2 << endl;
    unsigned long long int c2 = power(m2, e, n);
    cout << c2 << endl;

    unsigned long long int d2 = power(c2, d, n);
    cout << d2 << endl;

    unsigned long long int M = m1 * m2;
    cout << M << endl;
    unsigned long long int C = power(M, e, n);
    cout << C << endl;
    unsigned long long int D = power(C, d, n);
    cout << D << endl;
    if (M == D)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }

    cout << "Hello world!" << endl;
    return 0;
}