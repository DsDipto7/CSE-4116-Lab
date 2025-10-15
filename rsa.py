def gcd(a,b):
    while b:
        a %= b
        a, b = b, a
    return a

def power(a,b,c):
    res=1
    aa=a % c
    bb = b
    cc = c
    while bb > 0:
        if bb % 2 == 1:
            res = (res * aa) % cc
        aa = (aa * aa) % cc
        bb //= 2
    return res

def main():
    p = 100003
    q = 100019
    n = p * q
    print(f"Modulus n = p*q = {n}")
    fi_n = (p - 1) * (q - 1)
    print(f"Euler's totient fi_n = (p-1)*(q-1) = {fi_n}")
    e = 10000
    while e < fi_n:
        if gcd(e, fi_n) == 1:
            break
        e += 1
    print(f"Public key e = {e}")
    k = 0
    while True:
        if (1 + k * fi_n) % e == 0:
            d = (1 + k * fi_n) // e
            break
        k += 1
    print(f"Private key d = {d}")
    m1 = int(input("Enter first message (m1): "))
    print(f"Message m1 = {m1}")
    c1 = power(m1, e, n)
    print(f"Encrypted m1 (c1) = {c1}")
    d1 = power(c1, d, n)
    print(f"Decrypted c1 = {d1}")
    m2 = int(input("Enter second message (m2): "))
    print(f"Message m2 = {m2}")
    c2 = power(m2, e, n)
    print(f"Encrypted m2 (c2) = {c2}")
    d2 = power(c2, d, n)
    print(f"Decrypted c2 = {d2}")  
    M = m1 * m2
    print(f"Multiplicative M = m1 * m2 = {M}")
    C = power(M, e, n)
    print(f"Encrypted M (C) = {C}")
    D = power(C, d, n)
    print(f"Decrypted C = {D}")

    if M == D:
        print("Multiplicative property verified: YES")
    else:
        print("Multiplicative property verified: NO")

    print("Hello world!")

if __name__ == "__main__":
    main()
