#include <bits/stdc++.h>
using namespace std;

#define MAX_ROW 100
#define MAX_COL 100

string encryptMsg(string msg, int colOrder[], int key)
{
    int col = key;
    int row = ceil((float)msg.size() / key);

    int totalCells = row * col;
    while (msg.size() < totalCells)
        msg += "*";

    char matrix[MAX_ROW][MAX_COL];
    int idx = 0;

    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < col; c++)
        {
            matrix[r][c] = msg[idx++];
        }
    }

    string cipher = "";
    for (int i = 0; i < col; i++)
    {
        int colIndex = colOrder[i] - 1;
        for (int r = 0; r < row; r++)
        {
            cipher += matrix[r][colIndex];
        }
    }

    cout << "Encrypted Message: " << cipher << endl;
    return cipher;
}

string decryptMsg(string cipher, int colOrder[], int key)
{
    int col = key;
    int row = ceil((float)cipher.size() / key);

    char matrix[MAX_ROW][MAX_COL];
    int idx = 0;

    for (int i = 0; i < col; i++)
    {
        int colIndex = colOrder[i] - 1;
        for (int r = 0; r < row; r++)
        {
            matrix[r][colIndex] = cipher[idx++];
        }
    }

    string plain = "";
    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < col; c++)
        {
            plain += matrix[r][c];
        }
    }

    while (!plain.empty() && plain.back() == '*')
        plain.pop_back();

    cout << "Decrypted Message: " << plain << endl;
    return plain;
}

int main()
{
    string msg;
    cin >> msg;

    int key = 4;
    int colOrder[] = {4, 1, 2, 3};

    string cipher = encryptMsg(msg, colOrder, key);
    string plain = decryptMsg(cipher, colOrder, key);
}
