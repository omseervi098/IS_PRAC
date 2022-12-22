#include<bits/stdc++.h>
using namespace std;
string encryption(string pt,int key){
    for(auto &i:pt){
        if(isupper(i))
            i=(i+key-'A')%26+'A';
        else if(islower(i))
            i=(i+key-'a')%26+'a';
        else
            i=i;
    }
    return pt;
}
string decryption(string ct,int key){
    for(auto &i:ct){
        if(isupper(i))
            i=(i-key-'A'+26)%26+'A';
        else if(islower(i))
            i=(i-key-'a'+26)%26+'a';
        else
            i=i;
    }
    return ct;
}
int main(){
    string pt,ct;
    int key;
    cout<<"Enter the plain text: ";
    getline(cin,pt);
    cout<<"Enter the key: ";
    cin>>key;
    ct=encryption(pt,key);
    cout<<"The cipher text is: "<<ct<<endl;
    cout<<"Decrypted text is: "<<decryption(ct,key);
}