#include <bits/stdc++.h>
#include <vector>
using namespace std;
#define pb push_back
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define sz(x) (int)(size(x))
#define ll long long
#define vi vector<int>
#define vll vector<ll>
#define vvi vector<vector<int>>
#define pii pair<int,int>
#define umap unordered_map
#define uset unordered_set
const static int mod = 1e9+7;

vvi res;
void hamiltonianCyclePath(int src, vvi& adj, int idx, vector<int>& path, uset<int>& st){
    int n = sz(adj);
    if(idx==n){
        if(adj[path.back()][src]==1)
            res.pb(path);
        return;
    }
    for(int i=0;i<n;i++){
        if(i==src || st.count(i) || adj[path[idx-1]][i]==0)continue;
        path.pb(i);
        st.insert(i);
        hamiltonianCyclePath(src, adj, idx+1, path, st);
        path.pop_back();
        st.erase(i);
    }
}
int main() {
    int n;
    cin >> n;

    vvi adj(n, vi(n));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> adj[i][j];
        }
    }

    int src = 0;
    vector<int> path;
    uset<int> st;

    path.pb(src);
    st.insert(src);

    hamiltonianCyclePath(src, adj, 1, path, st);

    if(res.empty()) {
        cout << "No Hamiltonian Cycle\n";
    } else {
        for(auto cycle : res) {
            for(int x : cycle) {
                cout << x << " ";
            }
            cout << src; // print return to source
            cout << "\n";
        }
    }

    return 0;
}