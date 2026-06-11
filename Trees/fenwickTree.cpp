#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct BIT{
    int n;
    vector<ll> bit;

    void init(int cnt){
        n = cnt;
        bit.assign(cnt+1, 0); // 1 indexed
    }

    void build(vector<ll> &arr){ // optional but faster
        n = arr.size() - 1;
        bit.assign(n+1, 0);

        for(int i=1;i<=n; i++){
            bit[i] += arr[i];
            int parent = i + (i&(-1));
            if(parent <= n) bit[parent]+=bit[i];
        }
    }

    void update(int i, ll val){
        for(; i <= n; i+=(i&(-1))){
            bit[i] += val;
        }
    }
    ll query(int i){ // pref[1...i]
        ll s=0;
        for(; i>0; i -= (i&(-1))){
            s+=bit[i];
        }
        return s;
    }
    ll query(int l, int r){ // BIT : only for invertible ops!
        return query(r)-query(l-1);
    }
};
/**
 * see ops, change to class if needed
 */