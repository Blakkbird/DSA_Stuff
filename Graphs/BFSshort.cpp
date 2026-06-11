#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> bfs(int nodes, vector<vector<int>>& adj, int s) {
    vector<vector<int>> res;
    vector<bool> vis(nodes, false);

    queue<int> q;
    q.push(s);
    vis[s] = true;
    int level=0;

    while (!q.empty()) {
        int size = q.size();
        res.push_back({});

        for (int i = 0; i < size; i++) {
            int cur = q.front();
            q.pop();
            res[level].push_back(cur);

            for (int nei : adj[cur]) {
                if (!vis[nei]) {
                    vis[nei] = true; // Mark
                    q.push(nei);
                }
            }
        }
        level++;
    }
    return res;
}
bool dfs(vector<vector<int>>& adj, int s, int d, vector<int>& parent, vector<bool>& vis){ // NOT shortest unweighted !!
    vis[s]=true;
    if(s==d){
        return false;
    }
    for(int nei : adj[s]){
        if(!vis[nei]){
            parent[nei]=s;
            if(dfs(adj, nei, d, parent, vis)) // nei is new src for dfs
                return true; // propogate answer FASTER THIS WAY
        }
    }
}
vector <int> walk (int nodes, vector<vector<int>>& adj, int s, int d){
    vector <int> parent(nodes);
    vector <bool> vis(nodes);
    parent[s]=-1;

    dfs(adj, s, d, parent, vis);

    return parent;
}

int main() {
    int n = 6; 
    vector<vector<int>> adj(n);

    // Build a sample graph (Adjacency List)
    // 0 -- 1 -- 2
    // |    |
    // 3 -- 4 -- 5
    adj[0] = {1, 3};
    adj[1] = {0, 2, 4};
    adj[2] = {1};
    adj[3] = {0, 4};
    adj[4] = {1, 3, 5};
    adj[5] = {4};

    // Run BFS starting from node X
    cout << "Starting BFS from node 0..." << endl;
    vector<vector<int>> result = bfs(n, adj, 0);

    // Print results by level
    for (int i = 0; i < result.size(); i++) {
        cout << "Level " << i << ": ";
        for (int node : result[i]) {
            cout << node << " ";
        }
        cout << endl;
    }

    vector <int> path=walk(n, adj, 0, 5); // src, dest

    for(int i=5;i != -1; i=path[i]){
        cout << i << " <- ";
    }
    cout << 'X' << endl;

    return 0;
}