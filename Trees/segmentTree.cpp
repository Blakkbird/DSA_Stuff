// ===================================================================
// SIMPLE SEGMENT TREE  (point update + range sum)
// ===================================================================
// For a generic version (min / max / custom nodes) see genSegTree.cpp.
// For range updates see lazySegmentTree.cpp.
//
// IDEA
//   Each node stores the answer (here: the sum) for one segment [low, high].
//   The root covers the whole array; each node splits its segment in half
//   between its two children. Leaves are single elements.
//
/*   Example a = [5, 2, 7, 1]
                      [0,3]=15
                    /          \
              [0,1]=7          [2,3]=8
              /    \           /     \
           [0]=5  [1]=2     [2]=7   [3]=1
     (diagram is in a block comment because a // line ending in '\'
      would swallow the next line into the comment too)              */
//
// LAYOUT (no pointers)
//   node 1 = root, children of node v are 2v and 2v+1.
//   4n slots are always enough.
//
// COMPLEXITY
//   build O(n), update O(log n), query O(log n)
//
// TO CHANGE THE OPERATION (e.g. min instead of sum) change the 3 lines
// marked "op": the merge in build/update, the merge in query, and the
// "no overlap" return value (0 for sum, LLONG_MAX for min, ...).
// ===================================================================
#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct SegTree {
    int n;
    vector<ll> tree;

    // vector<ll> &a: pass by reference, so the array isn't copied
    void init(vector<ll> &a) {
        n = a.size();
        tree.assign(4 * n, 0);
        build(1, 0, n - 1, a);
    }

    // node covers [low, high]
    void build(int node, int low, int high, vector<ll> &a) {
        if (low == high) {                          // leaf = one element
            tree[node] = a[low];
            return;
        }
        // low + (high-low)/2 is the same as (low+high)/2 but can't overflow;
        // >>1 is a right shift = divide by 2
        int mid = low + ((high - low) >> 1);
        build(2 * node, low, mid, a);
        build(2 * node + 1, mid + 1, high, a);
        tree[node] = tree[2 * node] + tree[2 * node + 1];   // op
    }

    // set a[pos] = val: go down to the leaf, then fix sums on the way up
    void update(int node, int low, int high, int pos, ll val) {
        if (low == high) {
            tree[node] = val;                       // use += val for "add to a[pos]"
            return;
        }
        int mid = low + ((high - low) >> 1);
        if (pos <= mid) update(2 * node, low, mid, pos, val);
        else            update(2 * node + 1, mid + 1, high, pos, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];   // op
    }

    // sum of a[l..r]
    ll query(int node, int low, int high, int l, int r) {
        if (r < low || high < l) return 0;                  // no overlap  (op: identity)
        if (l <= low && high <= r) return tree[node];       // fully inside
        int mid = low + ((high - low) >> 1);                // partial: ask both halves
        return query(2 * node, low, mid, l, r)
             + query(2 * node + 1, mid + 1, high, l, r);    // op
    }

    // wrappers: same name, different parameters = "function overloading".
    // These are what you call; they always start at the root (node 1, [0, n-1]).
    void update(int pos, ll val) { update(1, 0, n - 1, pos, val); }
    ll query(int l, int r) { return query(1, 0, n - 1, l, r); }
};

/*
 * USAGE
 *   vector<ll> a = {5, 2, 7, 1};
 *   SegTree st;
 *   st.init(a);
 *   st.query(1, 3);     // 2 + 7 + 1 = 10
 *   st.update(2, 0);    // a[2] = 0
 *   st.query(1, 3);     // 2 + 0 + 1 = 3
 */
