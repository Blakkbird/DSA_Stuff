// ===================================================================
// GENERIC SEGMENT TREE  (point update + range query)
// ===================================================================
//
// WHAT IT DOES
//   Stores an array a[0..n-1] and supports, each in O(log n):
//     update(pos, u)      -> change a single element
//     query(l, r)         -> "combine" a[l..r]  (sum / min / max / anything)
//     find_first(l, r, p) -> first index in [l, r] where predicate p turns true
//
// WHY "GENERIC"
//   The tree itself never knows *what* it is combining. You give it two
//   small structs:
//     Node   - what each tree node stores + how two children combine
//     Update - how to change one leaf
//   So the same SegTree code handles sum, min, max-subarray, ... just by
//   swapping the Node/Update pair. That is what the template is for.
//
// CONVENTIONS
//   - array positions are 0-indexed: 0 .. n-1
//   - tree nodes are 1-indexed: root = 1, children of v are 2v and 2v+1
//     (this makes child math trivial, no pointers needed)
//   - all ranges [l, r] are INCLUSIVE on both ends
//
// NODE CONTRACT (what your Node struct must have)
//   Node()                                   identity element: merging with
//                                            it changes nothing (0 for sum,
//                                            +INF for min, ...)
//   Node(T val)                              build a leaf from an array value
//   void merge(const Node &l, const Node &r) set *this = l combined with r
//                                            (l is the LEFT part, order matters
//                                            for non-commutative ops)
//
// UPDATE CONTRACT
//   void apply(Node &a)                      modify one leaf in place
//
// USAGE
//   SegTree<NodeSum, UpdSum> st(a);          // a is vector<ll>
//   st.update(pos, UpdSum(5));
//   ll s = st.query(l, r).sum;
// ===================================================================
#include <bits/stdc++.h>
using namespace std;
using ll = long long;               // `using` is the modern C++ form of typedef
const ll INF = 1e18;                // ll, not int: values can exceed 1e9

// template<class Node, class Update>: Node and Update are "type parameters".
// The compiler generates a separate SegTree for every pair you use, e.g.
// SegTree<NodeSum, UpdSum> and SegTree<NodeMin, UpdMin> are different types.
template<class Node, class Update>
struct SegTree {
    int n = 0;                      // number of array elements
    vector<Node> tree;              // tree[1] is the root; tree[0] is unused

    SegTree() {}

    // empty tree of size sz, every leaf is the identity
    // `explicit` stops accidental conversions like  SegTree st = 5;
    explicit SegTree(int sz) : n(sz), tree(4 * sz) {}

    // build from an array. template<class T> lets a be vector<int>,
    // vector<ll>, ... anything that Node(T) can turn into a leaf.
    //
    // Why 4n nodes? The tree height is ceil(log2 n) and a full tree of that
    // height has < 4n nodes. 4n is the simple, always-safe bound.
    template<class T>
    explicit SegTree(const vector<T> &a) : n(a.size()), tree(4 * a.size()) {
        if (n > 0) build(1, 0, n - 1, a);
    }

    // recompute node v from its two children (the "go back up" step)
    void pull(int v) {
        tree[v].merge(tree[2 * v], tree[2 * v + 1]);
    }

    // node v covers the array segment [lo, hi]
    // leaf -> copy the value; otherwise build both halves, then pull. O(n)
    template<class T>
    void build(int v, int lo, int hi, const vector<T> &a) {
        if (lo == hi) {
            tree[v] = Node(a[lo]);
            return;
        }
        int mid = (lo + hi) / 2;
        build(2 * v, lo, mid, a);           // left child covers [lo, mid]
        build(2 * v + 1, mid + 1, hi, a);   // right child covers [mid+1, hi]
        pull(v);
    }

    // walk from the root down to the leaf `pos`, change it, then pull every
    // ancestor on the way back up. Only one root-to-leaf path: O(log n)
    void upd(int v, int lo, int hi, int pos, Update &u) {
        if (lo == hi) {
            u.apply(tree[v]);
            return;
        }
        int mid = (lo + hi) / 2;
        if (pos <= mid) upd(2 * v, lo, mid, pos, u);
        else            upd(2 * v + 1, mid + 1, hi, pos, u);
        pull(v);
    }

    // three cases for node v covering [lo, hi] vs. the query [l, r]:
    //   1) no overlap      -> return identity (contributes nothing)
    //   2) fully inside    -> return the stored answer, don't go deeper
    //   3) partial overlap -> ask both children and merge
    // At most ~4 nodes per level are visited -> O(log n)
    Node qry(int v, int lo, int hi, int l, int r) {
        if (r < lo || hi < l) return Node();
        if (l <= lo && hi <= r) return tree[v];
        int mid = (lo + hi) / 2;
        Node left  = qry(2 * v, lo, mid, l, r);
        Node right = qry(2 * v + 1, mid + 1, hi, l, r);
        Node res;
        res.merge(left, right);             // left first: merge may not be commutative
        return res;
    }

    // TREE WALK / "binary search on the tree"
    // Finds the smallest idx in [l, r] such that pred(merge of a[l..idx]) is true.
    // pred must be monotone over the prefix: false, false, ..., true, true.
    // Returns -1 if it never becomes true.
    //
    // acc = everything merged so far (to the left of the current node).
    // Passed by reference (Node &acc) so changes are seen by the caller.
    template<class F>
    int walk(int v, int lo, int hi, int l, int r, Node &acc, F pred) {
        if (r < lo || hi < l) return -1;
        if (l <= lo && hi <= r) {
            Node nxt;
            nxt.merge(acc, tree[v]);
            if (!pred(nxt)) {               // the whole node isn't enough:
                acc = nxt;                  // take all of it and keep going right
                return -1;
            }
            // the answer is inside this node -> descend without recursion:
            // try the left child; if it's enough go left, else take it and go right
            while (lo < hi) {
                int mid = (lo + hi) / 2;
                Node t;
                t.merge(acc, tree[2 * v]);
                if (pred(t)) {
                    v = 2 * v;
                    hi = mid;
                } else {
                    acc = t;
                    v = 2 * v + 1;
                    lo = mid + 1;
                }
            }
            return lo;
        }
        int mid = (lo + hi) / 2;
        int res = walk(2 * v, lo, mid, l, r, acc, pred);    // left part first
        if (res != -1) return res;
        return walk(2 * v + 1, mid + 1, hi, l, r, acc, pred);
    }

    // ---------------- public API (use these) ----------------
    void update(int pos, Update u) { upd(1, 0, n - 1, pos, u); }

    Node query(int l, int r) {
        if (l > r) return Node();
        return qry(1, 0, n - 1, l, r);
    }

    Node all() { return n > 0 ? tree[1] : Node(); }   // whole array, O(1)

    // F is the lambda's type; the compiler deduces it for you
    template<class F>
    int find_first(int l, int r, F pred) {
        if (l > r) return -1;
        Node acc;                           // starts as identity
        return walk(1, 0, n - 1, l, r, acc, pred);
    }
};

// ===================================================================
// READY-MADE NODES: copy the pair you need, delete the rest
// ===================================================================

// 1) RANGE SUM, point assign
struct NodeSum {
    ll sum = 0;                                     // identity: 0
    NodeSum() {}
    NodeSum(ll val) : sum(val) {}
    void merge(const NodeSum &l, const NodeSum &r) { sum = l.sum + r.sum; }
};
struct UpdSum {
    ll val;
    UpdSum(ll v) : val(v) {}
    void apply(NodeSum &a) { a.sum = val; }         // use  a.sum += val  for point add
};

// 2) RANGE MIN, point assign   (for max: identity -INF and use max)
struct NodeMin {
    ll mn = INF;                                    // identity: +INF (min(x, INF) = x)
    NodeMin() {}
    NodeMin(ll val) : mn(val) {}
    void merge(const NodeMin &l, const NodeMin &r) { mn = min(l.mn, r.mn); }
};
struct UpdMin {
    ll val;
    UpdMin(ll v) : val(v) {}
    void apply(NodeMin &a) { a.mn = val; }
};

// 3) MAX SUBARRAY SUM (non-empty) on a range. Classic "store more than the
//    answer" trick: a node keeps
//      sum  = total sum of the segment
//      pre  = best sum of a prefix
//      suf  = best sum of a suffix
//      best = best sum of any subarray
//    Best subarray of (L|R) is either inside L, inside R, or crosses the
//    middle = L.suf + R.pre. merge is NOT commutative (order matters).
struct NodeGss {
    ll sum = 0, pre = -INF, suf = -INF, best = -INF;  // identity (empty)
    NodeGss() {}
    NodeGss(ll val) : sum(val), pre(val), suf(val), best(val) {}
    void merge(const NodeGss &l, const NodeGss &r) {
        sum  = l.sum + r.sum;
        pre  = max(l.pre, l.sum + r.pre);
        suf  = max(r.suf, r.sum + l.suf);
        best = max({l.best, r.best, l.suf + r.pre});  // max({...}) takes a list
    }
};
struct UpdGss {
    ll val;
    UpdGss(ll v) : val(v) {}
    void apply(NodeGss &a) { a = NodeGss(val); }
};

// 4) ZERO RUNS: for "count subarrays containing at least one mark".
//    Leaf = 1 if the position is marked, 0 otherwise.
//    A run of g unmarked cells contains T(g) = g(g+1)/2 subarrays with no mark.
//    Node stores
//      len = segment length
//      pre = length of the unmarked run touching the left edge
//      suf = length of the unmarked run touching the right edge
//      sum = sum of T(g) over all unmarked runs
//    When gluing L|R, L's suffix run and R's prefix run join into one run,
//    so remove their separate counts and add the joined one.
//    Answer for window [L, R] = T(R - L + 1) - query(L, R).sum
struct NodeRun {
    ll len = 0, pre = 0, suf = 0, sum = 0;
    static ll T(ll x) { return x * (x + 1) / 2; }   // static: belongs to the type, no object needed
    NodeRun() {}
    NodeRun(ll mark) : len(1), pre(!mark), suf(!mark), sum(!mark) {}
    void merge(const NodeRun &l, const NodeRun &r) {
        len = l.len + r.len;
        sum = l.sum + r.sum - T(l.suf) - T(r.pre) + T(l.suf + r.pre);
        pre = (l.pre == l.len) ? l.len + r.pre : l.pre;   // L all unmarked -> run continues into R
        suf = (r.suf == r.len) ? r.len + l.suf : r.suf;
    }
};
struct UpdRun {
    ll mark;
    UpdRun(ll m) : mark(m) {}
    void apply(NodeRun &a) { a = NodeRun(mark); }
};

// ===================================================================
// EXAMPLE
// ===================================================================
// vector<ll> a(n);
// for (auto &x : a) cin >> x;
// SegTree<NodeSum, UpdSum> st(a);
// cout << st.query(l, r).sum << '\n';
// st.update(pos, UpdSum(v));
//
// first index where the running prefix sum reaches `need`
// ([&] means the lambda can read local variables like `need` by reference):
// int idx = st.find_first(0, n - 1, [&](const NodeSum &x) { return x.sum >= need; });
//
// HOW TO WRITE YOUR OWN NODE
//   1. what must a node store so that two children are enough to compute
//      the parent? (often more than just the answer, see NodeGss)
//   2. what is the identity? (merging it in must change nothing)
//   3. write merge(l, r) carefully: l is the left part
