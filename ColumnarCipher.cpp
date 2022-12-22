#include<bits/stdc++.h>
using namespace std;
string encryption(vector<vector<char>> &v,vector<pair<char,int>> &v1,int m,int n){
    string ct=""; 
    for(auto [a,i]:v1){
        for(int j=0;j<m;j++){
            ct+=v[j][i];
        }
    }
    return ct;
    
}
string decryption(vector<vector<char>> &v,vector<pair<char,int>> &v1,int m,int n){
    string pt="";
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(v[i][j]=='X'){
                pt+=' ';
                continue;
            }
            if(v[i][j]=='_') break;
            pt+=v[i][j];
        }
    }
    return pt;
}
int main(){
    string pt,ct,key;
    cout<<"Enter the plain text: ";
    getline(cin,pt);
    cout<<"Enter the key: ";
    cin>>key;
    int n=key.size();  // no. of columns
    int m=ceil(pt.size()/(double)n); // no. of rows
  
    vector<vector<char>> v(m,vector<char>(n,' '));
    int k=0;
    for(auto &i:v){
        for(auto &j:i){
            if(k>=pt.size())
            {
                j='_';
                k++;
                continue;
            }
            if(pt[k]==' '){
                j='X';
                k++;
                continue;
            }
            j=pt[k++];
        }
    }
    vector<pair<char,int>> v1;
    for(int i=0;i<n;i++)
        v1.push_back({key[i],i});
    sort(v1.begin(),v1.end());
    ct=encryption(v,v1,m,n);
    cout<<"The cipher text is: "<<ct<<endl;
    cout<<"Decrypted text is: "<<decryption(v,v1,m,n);
}
