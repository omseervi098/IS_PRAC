/*
    1. Take a 64 bit input
    2. Divide it into 2 parts LPT and RPT of 32 bits each
    3. Prepare a function with the following rounds :
        a. Take RPT as input and expand it into 48 bits using an expansion permutation table
        b. XOR result of step 3.1 and a 48 bit key
        c. Convert the result of step 3.2 into a 32 bit value using an s box substitution.
    4. Move out of the function block and XOR with 32 bit LPT
    5. Swap LPT and RPT
    6. Repeat the Process one more time with a new 48 bit key and expansion permutation tables.
    7. finally swap after 2 rounds and concatenate LPT and RPT to obtain the 64 bit Ciphertext
*/
#include<bits/stdc++.h>
using namespace std;
int sbox[2][4][16]={
    {
       {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
       {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
       {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
       {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    },
    {
        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
    }
   };
string xorof(string a,string b){
    string ans="";
    for(int i=0;i<a.size();i++){
        if(a[i]=='0' and b[i]=='1'){
            ans+='1';
        }else if(a[i]=='1' and b[i]=='0'){
            ans+='1';
        }else{
            ans+='0';
        }
    }
    return ans;
}
string Rounds(string RPT,string key,int m){
    //Expanding RPT from 32 bits to 48 bits
    string temp="";
    int k=0,l=3;
    for(int i=0;i<32;i++){
        if(i==k||i==l){
            if(i==l){
                
                temp+=RPT[i];
                temp+=RPT[(i+1)%32];
                l+=4;
                
            }
            if(i==k) {
                temp+=RPT[(i-1+32)%32];
                temp+=RPT[i];
                k+=4;
            }
        }
        else{
            temp+=RPT[i];         
        }
    }
    temp=xorof(temp,key);
    k=0,l=5;
    string ans="";
    for(int i=0;i<48;i+=6){
        string t1=temp.substr(i,6);
        string t2="";
        t2+=t1[0];
        t2+=t1[5];
        string t3=t1.substr(1,4);
        int row=std::bitset<4>(t2).to_ulong();
        int col=std::bitset<4>(t3).to_ulong();
        ans+=std::bitset<4>(sbox[m][row][col]).to_string();
    }
    return ans;
}
void swap(string &a,string &b){
    string t=a;
    a=b;
    b=t;
}
string DES(string s,string key){
    string pt="";
    for(auto i:s){
        pt+=std::bitset<8>((int)i).to_string();
    }
    string k="";
    for(auto i:key){
        k+=std::bitset<8>((int)i).to_string();
    }
    string LPT=pt.substr(0,32),RPT=pt.substr(32);
    string k1=k.substr(0,48),k2=k.substr(48);
    //ROUND 1
    string temp=Rounds(RPT,k1,0);
    temp=xorof(LPT,temp);
    swap(LPT,RPT);
    //ROUND 2
    temp=Rounds(RPT,k2,1);
    temp=xorof(LPT,temp);
    swap(LPT,RPT);
    return LPT+RPT;
}
int main(){
   string s,key;
   cout<<"Enter text of 8 characters: ";
   cin>>s; //64 bit plain text
   cout<<"Enter key of 12 characters: ";
   cin>>key; //96bits key
    
   string ct=DES(s,key);
  
   cout<<"Cipher text: "<<ct<<endl; 
}