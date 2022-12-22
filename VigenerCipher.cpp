#include<bits/stdc++.h>
using namespace std;
string encryption(string pt,string key){
    for(int i=0;i<pt.size();i++){
        if(isupper(pt[i]))
            pt[i]=(pt[i]+key[i])%26+'A';
        else if(islower(pt[i]))
            pt[i]=(pt[i]+key[i])%26+'a';
    }
    return pt;
}
string decryption(string ct,string key){
    for(int i=0;i<ct.size();i++){
        if(isupper(ct[i]))
            ct[i]=(ct[i]-key[i]+26)%26+'A';
        else if(islower(ct[i]))
            ct[i]=(ct[i]-key[i]+26)%26+'a';
    }
    return ct;
}
int main(){
    string pt,ct,key;
    cout<<"Enter the plain text: ";
    getline(cin,pt);
    cout<<"Enter the key: ";
    cin>>key;
    while(key.size()<pt.size())
        key+=key;
    cout<<key<<endl;
    ct=encryption(pt,key);
    cout<<"The cipher text is: "<<ct<<endl;
    cout<<"Decrypted text is: "<<decryption(ct,key);
}