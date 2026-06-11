#include <bits/stdc++.h>
using namespace std;
#define ll long long 

struct sparseTable{ 
    int n;
    int loglog;

    vector<vector<ll>> mat;
    vector<ll> lg; // lg[i] = floor(log_2 (i))

    ll op (ll a, ll b){
        return min(a, b); // set idempotent Oper. here
    }
    void build(vector<ll> &arr){
        n = arr.size();
        lg.assign(n+1, 0);

        for(int i=2;i<=n; i++){
            lg[i] = lg[i/2] + 1; // floor(log2) by recurr.
        }

        loglog = lg[n]+1;
        mat.assign(loglog, vector<ll>(n));

        for(int i=0;i<n;i++){
            mat[0][i] = arr[i]; // lvl 0 - individual elements
        }

        for(int k=1;k < loglog; k++){
            for(int i=0; i+(1<<k) <= n; i++){
                mat[k][i] = op(mat[k-1][i], mat[k-1][i + (1<< (k-1))]);
            }
        }
    }

    ll query(int l, int r){
        int k = lg[r-l+1];
        return op(mat[k][l], mat[k][r - (1<<k) + 1]);
    }
};