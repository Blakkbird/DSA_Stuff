#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

typedef pair<int,int> nodei; // (node, weight) or other variation...

int dijkstra(vector<vector<nodei>>& adj, int src, int dest, int n, vector<int>& parent){
    vector <int> dist(n, INT_MAX);
    priority_queue <nodei, vector<nodei>, greater<nodei>> pq; // min heap
    dist[src]=0;
    parent[src]=-1;
    pq.push({0, src}); // min heap w/ (DIST, NODE)

    while(!pq.empty()){
        auto [d, u]=pq.top(); pq.pop();
        
        if(d > dist[u])
            continue; // already relaxed this
        
        for(auto [v, wt] : adj[u]){ // explore neighbours
            if(d+wt < dist[v]){
                dist[v]=d+wt;
                parent[v]=u;
                pq.push({dist[v], v}); // emplace so it can be further explored
            }
        }
    }

    return dist[src];
}

int main(){
    int n = 5;
    vector<vector<nodei>> adj(n);
    vector<int> parent(n, -1), path;

    // Example graph (undirected)
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

    int dist = dijkstra(adj, 0, 4, n, parent);
    cout << "Min dist: " << dist << endl;

    // Build path
    for(int cur = 4; cur != -1; cur = parent[cur]) {
        path.push_back(cur);
    }

    reverse(path.begin(), path.end());

    cout << "Path: ";
    for(int i = 0; i < path.size(); i++){
        if(i) cout << " -> ";
        cout << path[i];
    }
    cout << endl;

    return 0;
}
