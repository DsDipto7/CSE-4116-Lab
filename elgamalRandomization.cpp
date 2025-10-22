#include<bits/stdc++.h>
using namespace std;
long long modexp(long long base, long long exp, long long mod){
    base=base%mod;
    long long res=1;
    while(exp>0){
        if(exp%2==1){
            res=(res*base)%mod;
        }
        base=(base*base)%mod;
        exp /=2;
    }
    return res;
}

long long modinv(long long a, long long p){
    return modexp(a,p-2,p);
}
int main()
{
    long long p=11;
    long long alpha=2;
    long long a=6;
    long long beta=modexp(alpha,a,p);
    cout<<"Prime Number :"<<p<<endl;
    cout<<"Beta :"<<beta<<endl;
    cout<<"Private Key :"<<a<<endl;

    long long m=9;
    long long k=7;

    long long y1=modexp(alpha,k,p);
    long long y2= (m*modexp(beta,k,p))%p;
    cout<<"Original Cipher :"<<y1 <<" and " << y2<<endl;
    
    long long r=4;
    long long y1_new = modexp(alpha, r, p);
    long long y2_new = (m * modexp(beta, r, p)) % p;
    cout << "Rerandomized Cipher :" << y1_new << " and " << y2_new << endl;

    long long m1= (y2*modinv(modexp(y1,a,p),p))%p;
    long long m2 = (y2_new * modinv(modexp(y1_new, a, p), p)) % p;

    cout << "\nDecrypted (original) = " << m1;
    cout << "\nDecrypted (rerandomized) = " << m2 << "\n";
}