#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

typedef pair<int,int> nodei; // (wt, node)

// PRIM'S FUNCTION
vector<nodei> prims(vector<vector<nodei>>& adj, int n){
    vector<int> dist(n, INT_MAX), parent(n, -1);
    vector<bool> inMST(n, false);

    int src = 0;
    dist[src] = 0;

    priority_queue<nodei, vector<nodei>, greater<nodei>> pq;
    pq.push({0, src});

    while(!pq.empty()){
        auto [w, u] = pq.top(); 
        pq.pop();
        if(inMST[u]) continue;
        // add w to MST weight !
        inMST[u] = true;

        for(auto &nei : adj[u]){
            int v = nei.first;
            int wt = nei.second;

            if(!inMST[v] && wt < dist[v]){ // dist. from u to v CAN be relaxed
                dist[v] = wt;
                parent[v] = u;
                pq.push({wt, v});
            }
        }
    }

    // Build MST edges
    vector<nodei> mstEdges;
    for(int v = 1; v < n; v++){
        // v = 0 has no parent
        mstEdges.push_back({parent[v], v});
    }

    return mstEdges;
}

// --------------------- MAIN ----------------------
int main(){
    int n = 5;
    vector<vector<nodei>> adj(n);

    // undir. node-wt
    adj[0].push_back({1, 2});
    adj[1].push_back({0, 2});

    adj[1].push_back({2, 4});
    adj[2].push_back({1, 4});

    adj[0].push_back({3, 1});
    adj[3].push_back({0, 1});

    adj[3].push_back({4, 7});
    adj[4].push_back({3, 7});

    adj[2].push_back({4, 3});
    adj[4].push_back({2, 3});

    // Get MST
    vector<pair<int,int>> mst = prims(adj, n);

    int totalWeight = 0;

    cout << "MST Edges:\n";
    for(auto &p : mst){
        int u = p.first;
        int v = p.second;

        // Find the weight
        int wt = -1;
        for(auto &x : adj[u]) 
            if(x.first == v) wt = x.second;

        cout << u << " - " << v << " (wt = " << wt << ")\n";
        totalWeight += wt;
    }

    cout << "Total MST Weight = " << totalWeight << endl;

    return 0;
}
