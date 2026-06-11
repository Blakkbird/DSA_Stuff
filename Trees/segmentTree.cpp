#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct SegTree{
    int n;
    vector<ll> tree, lazy, arr;

    void init(vector<ll> &a){
        n = a.size();
        arr = a;
        tree.assign(4*n, 0);
        tree.assign(4*n, 0);
        build(1, 0, n-1); // note 1 indexed
    }

    void build(int node, int low, int high){
        if(low==high){
            tree[node]=arr[low];
            return;
        }

        int mid = low + ((high-low)>>1);
        build(2*node, low, mid);
        build(2*node + 1, mid+1, high);

        tree[node] = tree[2*node]+tree[2*node + 1]; // replace op here
    }

    void applyUpdate(int node, int low, int high, ll val){ // range update push
        tree[node] += val*(high-low+1); // op specific
        lazy[node] += val; // park for children (accumulate)
    }
    void push_down(int node, int low, int high){ // flush vals 
        if(lazy[node]==0)return;

        int mid = low + ((high-low)>>1);
        applyUpdate(2*node, low, mid, lazy[node]);
        applyUpdate(2*node + 1, mid+1, high, lazy[node]);

        lazy[node]=0; // clear
    }

    void update(int node, int low, int high, int l, int r, ll val){ // add range update on [l, r]
        if(r < low || l > high)return;
        
        if(l <= low && high <= r){
            applyUpdate(node, low, high, val);
            return;
        }

        push_down(node, low, high);
        int mid = low + ((high-low)>>1);
        update(2*node, low, mid, l, r, val);
        update(2*node + 1, mid+1, high, l, r, val);

        tree[node]=tree[2*node] + tree[2*node + 1];
    }

    ll query(int node, int low, int high, int l, int r){ // oper. over range [l, r]
        if(r < low || high < l)return 0;
        
        if(l <= low && high <= r)return tree[node]; // node fully in range

        push_down(node, low, high); // flush before descent
        int mid = low + ((high-low)>>1);
        return query(2*node, low, mid, l, r) + query(2*node +1, mid+1, high, l, r);
    }

    // wrappers
    void update(int l, int r, ll val){
        update(1, 0, n-1, l, r, val);
    }
    ll query(int l, int r){
        return query(1, 0, n-1, l, r);
    }
};
/**
 * SegTree tree1
 * tree1.init(array_name)
 * 
 * tree1.oper(...)
 */