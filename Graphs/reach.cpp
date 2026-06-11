#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

/**
 * Single Pair Reachability
 * Returns true if there is a path from s to t in G.
 */
bool isReachable(const vector<vector<int>>& adj, int s, int t, vector <bool>& vis) {
    if(s==t)
        return true;
    vis[s]=true;
    for(auto nei : adj[s]){
        if(!vis[nei] && isReachable(adj, nei, t, vis))
            return true;
    }
    return false;
}

int main() {
    // Example Graph (Adjacency List)
    // 0 -> 1, 2
    // 1 -> 2
    // 2 -> 0, 3
    // 3 -> 3
    int numNodes = 4;
    vector<vector<int>> adj(numNodes);
    adj[0] = {1, 2};
    adj[1] = {2};
    adj[2] = {0};
    adj[3] = {3};
    vector <bool> vis(adj.size(), false);

    int s = 0, t = 3;
    if (isReachable(adj, s, t, vis))
        cout << "Path exists from " << s << " to " << t << endl;
    else
        cout << "No path exists from " << s << " to " << t << endl;

    return 0;
}