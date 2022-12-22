#include<bits/stdc++.h>
using namespace std;
vector<string> process(string pt){
    int i=0;
    vector<string> res;
    for(i=0;i+16<pt.size();i+=16){
        string sub=pt.substr(i,16);
        string c="";
        for(auto i:sub){
            c+=std::bitset<8>((int)i).to_string();
        }
        res.push_back(c);
    }
    if(i<pt.size()){
        string sub= pt.substr(i,pt.size()-i);
        while(sub.size()<16){
            sub+=' ';
        }
        string c="";
        for(auto i:sub){
            c+=std::bitset<8>((int)i).to_string();
        }
        res.push_back(c);
    }
    return res;
}
string decryption(vector<string> ct,int key){
    for(auto &i:ct){
        reverse(i.begin(),i.begin()+i.size()-key);
        reverse(i.begin()+i.size()-key,i.end());
        reverse(i.begin(),i.end());
    }
    string pt="";
    for(auto i:ct){
        for(int j=0;j<128;j+=8){
            string temp=i.substr(j,8);
            int ans=std::bitset<8>(temp).to_ulong();
            pt+=(char)ans;
        }
    }
    return pt;
}
vector<string> encryption(vector<string> pt,int key){
    for(auto &i:pt){
        //circular left shift by key
        reverse(i.begin(),i.end());//12345
        reverse(i.begin(),i.begin()+i.size()-key);
        reverse(i.begin()+i.size()-key,i.end());
    }
    return pt;
}
int main(){
    string pt;
    cout<<"Enter the string: ";
    getline(cin,pt);
    cout<<pt.size()<<endl;
    int key;
    cout<<"Enter key: ";
    cin>>key;
    key%=128;
    vector<string> v=process(pt);
    cout<<endl;
    vector<string> c=encryption(v,key);
    cout<<"Encrypted Ciphers: "<<endl;
    for(auto i:c) cout<<i<<endl;
    cout<<"Decryption is: "<<decryption(c,key)<<endl;
}