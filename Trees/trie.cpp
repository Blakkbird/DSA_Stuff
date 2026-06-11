#include <bits/stdc++.h>
using namespace std;

class Trie{
    vector<array<int, 26>> nxt;
    vector<bool> end;

    int node(){
        nxt.emplace_back();
        nxt.back().fill(-1);
        end.push_back(false);
        return (int)nxt.size() -1;
    }

    public:
    
    Trie() {node();} // root

    void insert(const string &w){
        int cur=0;
        for(char c : w){
            int i=c-'a';
            if(nxt[cur][i] == -1){
                nxt[cur][i]=node();
            }
            cur=nxt[cur][i];
        }
        end[cur]=true;
    }
    bool search(const string& w) const{
        int cur = 0;
        for(char c : w){
            int i = c-'a';
            if(nxt[cur][i] == -1)return false;
            cur = nxt[cur][i];
        }
        return end[cur];
    }
};