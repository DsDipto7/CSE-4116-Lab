#include<bits/stdc++.h>
using namespace std;
#define max_r 100
#define max_c 100
string encrypted(string msg, int key, int order[]){
    int col=key;
    string cipher="";
    int row=ceil(float(msg.size())/key);
    int cell=row*col;
    while(msg.length()<cell){
        msg+="*";
    }
    char matrix [max_r][max_c];
    int x=0;
    for(int r=0;r<row;r++){
        for(int c=0;c<col;c++){
            matrix[r][c]=msg[x++];
        }
    }
    for(int i=0;i<col;i++){
        int colIn=order[i]-1;
        for(int j=0;j<row;j++){
            cipher +=matrix[j][colIn];
        }
    }
    cout<<"Encrypted : "<<cipher<<endl;
    return cipher;
    

}
void decrypt(string cipher,int key,int order[]){
    int col=key;
    int row = ceil(float(cipher.size())/key);
    char matrix [max_r][max_c];
    int x=0;
    for(int i=0;i<col;i++){
        int colIn=order[i]-1;
        for(int j=0;j<row;j++){
            matrix[j][colIn]=cipher[x++];
        }
    }
    string plain="";
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            plain+=matrix[i][j];
        }
    }
     while(!plain.empty() && plain.back()=='*'){
        plain.pop_back();
    }
        cout<<"Decrypted : "<<plain<<endl;
}
int main(){
    string msg;
    cin>>msg;
    int key=4;
    int order[]={4,1,2,3};
    string cipher=encrypted(msg,key,order);
    decrypt(cipher,key,order);
}