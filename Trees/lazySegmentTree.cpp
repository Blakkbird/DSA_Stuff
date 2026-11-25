// ===================================================================
// LAZY SEGMENT TREE  (range add + range sum)
// ===================================================================
// Read segmentTree.cpp first; this builds on it.
//
// THE PROBLEM
//   "add val to every a[i] in [l, r]" done as point updates is
//   (r-l+1) * O(log n), so O(n log n) per operation. Too slow.
//
// THE IDEA: be lazy
//   When an update fully covers a node, don't touch its children. Instead:
//     1. fix this node's sum right now:  sum += val * (segment length)
//     2. write a note in lazy[node]: "my children still owe +val each"
//   Later, if we ever need to go *below* that node (in an update or query),
//   we first hand the note down to the two children ("push down").
//   So work is only done on the paths we actually walk: O(log n) per op.
//
//   Invariant: tree[node] is always the CORRECT sum for its segment.
//              lazy[node] is what its children haven't received yet.
//
// COMPLEXITY
//   build O(n), range update O(log n), range query O(log n)
//
// TO CHANGE THE OPERATION, edit only:
//   applyUpdate  - how a pending value changes a node + how to stack it
//   the merges   - lines marked "op"
//   push_down's "nothing pending" check
//   (e.g. range assign: tree = val*len, lazy = val, use a separate flag
//    for "nothing pending" since 0 can be a real assigned value)
// ===================================================================
#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct LazySegTree {
    int n;
    vector<ll> tree, lazy;

    void init(vector<ll> &a) {
        n = a.size();
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);                  // 0 = nothing pending
        build(1, 0, n - 1, a);
    }

    void build(int node, int low, int high, vector<ll> &a) {
        if (low == high) {
            tree[node] = a[low];
            return;
        }
        int mid = low + ((high - low) >> 1);
        build(2 * node, low, mid, a);
        build(2 * node + 1, mid + 1, high, a);
        tree[node] = tree[2 * node] + tree[2 * node + 1];   // op
    }

    // apply "add val to every element" to the node covering [low, high]
    void applyUpdate(int node, int low, int high, ll val) {
        tree[node] += val * (high - low + 1);   // every element grew by val
        lazy[node] += val;                      // children still owe val (+= so notes stack)
    }

    // hand this node's note down to both children, then clear it
    void push_down(int node, int low, int high) {
        if (lazy[node] == 0) return;            // nothing pending
        int mid = low + ((high - low) >> 1);
        applyUpdate(2 * node, low, mid, lazy[node]);
        applyUpdate(2 * node + 1, mid + 1, high, lazy[node]);
        lazy[node] = 0;
    }

    // add val to a[l..r]
    void update(int node, int low, int high, int l, int r, ll val) {
        if (r < low || high < l) return;        // no overlap
        if (l <= low && high <= r) {            // fully covered: stop here, be lazy
            applyUpdate(node, low, high, val);
            return;
        }
        push_down(node, low, high);             // about to go deeper: settle old notes first
        int mid = low + ((high - low) >> 1);
        update(2 * node, low, mid, l, r, val);
        update(2 * node + 1, mid + 1, high, l, r, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];   // op: rebuild from children
    }

    // sum of a[l..r]
    ll query(int node, int low, int high, int l, int r) {
        if (r < low || high < l) return 0;                  // no overlap (identity)
        if (l <= low && high <= r) return tree[node];       // already correct, see invariant
        push_down(node, low, high);                         // children must be up to date
        int mid = low + ((high - low) >> 1);
        return query(2 * node, low, mid, l, r)
             + query(2 * node + 1, mid + 1, high, l, r);    // op
    }

    // wrappers (call these)
    void update(int l, int r, ll val) { update(1, 0, n - 1, l, r, val); }
    ll query(int l, int r) { return query(1, 0, n - 1, l, r); }
};

/*
 * USAGE
 *   vector<ll> a = {5, 2, 7, 1};
 *   LazySegTree st;
 *   st.init(a);
 *   st.update(1, 3, 10);  // a = {5, 12, 17, 11}
 *   st.query(0, 2);       // 5 + 12 + 17 = 34
 *   st.update(0, 1, -5);  // a = {0, 7, 17, 11}
 *   st.query(1, 1);       // 7
 */
