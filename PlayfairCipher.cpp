#include<bits/stdc++.h>
using namespace std;

void generatekeysquare(string key,vector<vector<char>> &v){
    vector<int> freq(26,0);
    for(auto i:key){
        if(i!='j'){
            freq[i-'a']++;
        }
    }
    int i=0,j=0;
    for(auto k:key){
        if(freq[k-'a']>0){
            v[i][j]=k;
            freq[k-'a']=-1;
            j++;
            if(j==5){
                i++;
                j=0;
            }
        }
    }
    for(int k=0;k<26;k++){
        if(freq[k]==0 and k+'a'!='j'){
            v[i][j]=k+'a';
            j++;
            if(j==5){
                i++;
                j=0;
            }
        }
    }
}
string preprocess(string pt){
    for(auto &i:pt){
        i=tolower(i);
        if(i=='j'){
            i='i';
        }
    }
    string res="";
    for(int i=0;i<pt.size();i++){
        if(i+1<pt.size() and pt[i]==pt[i+1]){
            res+=pt[i];
            res+='x';
        }
        else{
            res+=pt[i];
        }
    }
    
    if(res.length()%2==1){
        res+='z';
    }
    return res;
}
string search(vector<vector<char>> &v,char a,char b,bool decrypt){
    int x1,y1,x2,y2;
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if(v[i][j]==a){
                x1=i;
                y1=j;
            }
            if(v[i][j]==b){
                x2=i;
                y2=j;
            }
        }
    }
    if(y1==y2){
        if(decrypt){
            x1=(x1-1+5)%5;
            x2=(x2-1+5)%5;
        }
        else{
            x1=(x1+1)%5;
            x2=(x2+1)%5;
        }
    }
    else if(x1==x2){
        if(decrypt){
            y1=(y1-1+5)%5;
            y2=(y2-1+5)%5;
        }
        else{
            y1=(y1+1)%5;
            y2=(y2+1)%5;
        }
    }
    else{
        swap(y1,y2);
    }
    string res="";
    res+=v[x1][y1];
    res+=v[x2][y2];
    return res;
}
string encryption(string pt,vector<vector<char>> &kem){
    string res="";
    for(int i=0;i<pt.length();i+=2){
        res+=search(kem,pt[i],pt[i+1],false);
    }
    return res;
}
string decryption(string ct,vector<vector<char>> &kem){
    string res="";
    for(int i=0;i<ct.length();i+=2){
        res+=search(kem,ct[i],ct[i+1],true);
    }
    
    return res;
}
int main(){
    string pt,ct,key;
    cout<<"Enter the plain text: ";
    cin>>pt;
    cout<<"Enter the key: ";
    cin>>key;
    int n = pt.length();
    vector<vector<char>> kem(5,vector<char>(5));
    generatekeysquare(key,kem);
    pt=preprocess(pt);
    cout<<"After preprocessing: "<<pt<<endl;
    cout<<"The key square is: "<<endl;
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            cout<<kem[i][j]<<"  ";
        }
        cout<<endl;
    }
    ct=encryption(pt,kem);
    cout<<"The cipher text is: "<<ct<<endl;
    cout<<"Decrytion is: "<<decryption(ct,kem)<<endl;

}
