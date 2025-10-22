#include <iostream>
using namespace std;

// Vernam Cipher using XOR on long long integers
long long vernamEncrypt(long long message, long long key)
{
    return message ^ key; // XOR encryption
}

long long vernamDecrypt(long long cipher, long long key)
{
    return cipher ^ key; // XOR decryption (same operation)
}

int main()
{
    long long message, key;

    cout << "Enter message (as number): ";
    cin >> message;
    cout << "Enter key (as number): ";
    cin >> key;

    // Encryption
    long long cipher = vernamEncrypt(message, key);
    cout << "\nEncrypted Ciphertext = " << cipher << endl;

    // Decryption
    long long decrypted = vernamDecrypt(cipher, key);
    cout << "Decrypted Message = " << decrypted << endl;

    // Verification
    if (decrypted == message)
        cout << "\n Decryption successful! Original message recovered.\n";
    else
        cout << "\n Decryption failed.\n";

    return 0;
}
