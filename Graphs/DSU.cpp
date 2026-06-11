#include <bits/stdc++.h>
using namespace std;

class DSU{
    vector<int> parent, cnt;
    public:

    DSU(int n){
        parent.resize(n);
        cnt.assign(n, 1); // will resize
        for(int i=0;i<n;i++)parent[i]=i;
    }
    int find(int x){
        if(parent[x]!=x)
            return parent[x]=find(parent[x]);
        return parent[x];
    }
    bool unite(int a, int b){
        a = find(a);
        b = find(b);
        if(a==b)return false;

        if(cnt[a] < cnt[b])swap(a, b);
        parent[b]=a;
        cnt[a]+=cnt[b]; // rank not same as size!! size preferred
        return true;
    }
};
// nice Amortized analysis on this