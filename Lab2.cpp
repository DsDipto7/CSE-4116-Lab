#include<bits/stdc++.h>

using namespace std ;


#define ll long long



 //656692050181897513638241554199181923922955921760928836766304161790553989228223793461834703506872747071705167995972707253940099469869516422893633357693

 //204616454475328391399619135615615385636808455963116802820729927402260635621645177248364272093977747839601125961863785073671961509749189348777945177811

//10987
//10993


ll gcd(ll a, ll b) {
    return (b == 0) ? a : gcd(b, a % b);
}


ll modInverse(ll e, ll phi) {
    for (ll d = 1; d < phi; d++) {
        if ((d * e) % phi == 1)
            return d;
    }
    return -1;
}


ll powerMod(ll base, ll exp, ll mod) {
    ll result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp & 1)
            result = (result * base) % mod;

        exp >>= 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {

    ll p, q;
    p = 10987;
    q = 10993;



    ll n = p * q;
    ll phi = (p - 1) * (q - 1);


    ll e =10000 ;
    while (gcd(phi, e) != 1)
        e++;


    ll d = modInverse(e, phi);

    cout << "\nPublic Key  (e, n): " << e << ", " << n ;
    cout << "\nPrivate Key (d, n): " << d << ", " << n ;


    ll msg1,msg2;
    cout << "\nEnter message (as number): ";
    cin >> msg1>>msg2;

     cout << "\nMultiplication (m1*m2): "<<msg1*msg2<<endl;


    ll c,c1,c2;
    c1 = powerMod(msg1, e, n);
    c2 = powerMod(msg2,e,n);
c =c1*c2;


    cout << "Encrypted Message: c "<<c<<" c1= " << c1<<" c2= " << c2<<endl;


    ll decypted,decrypted1,decrypted2;

    decypted= powerMod(c, d, n);
     decrypted1 = powerMod(c1, d, n);
     decrypted2 = powerMod(c2, d, n);
    cout << "Decrypted Message:"<<decypted<<" decryt1= " <<  decrypted1<<" decrypt2= " <<  decrypted2<<endl;

    return 0;
}





