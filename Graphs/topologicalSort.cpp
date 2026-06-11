#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;
// can't for undirected + cycles (stop at node before cycle)
vector<int> topoSort(vector<vector<int>>& adj) { // Kahn - Directed Acyclic Graph
    int n = adj.size();
    vector<int> indegree(n, 0);
    queue<int> q;
    vector<int> list;

    // Compute indegrees
    for (int i = 0; i < n; i++) { // node -> next[i]
        for (int next : adj[i])
            indegree[next]++;
    }

    // Add all nodes with indegree 0 
    for (int i = 0; i < n; i++)
        if (indegree[i] == 0)
            q.push(i);

    // Kahn’s Algorithm (BFS)
    while (!q.empty()) {
        int top = q.front();
        q.pop();
        list.push_back(top);
        for (int next : adj[top]) {
            indegree[next]--;
            if (indegree[next] == 0)
                q.push(next);
        }
    }

    return list;
}
void dfs(int node, vector<vector<int>>& adj, vector<int>& vis, stack<int>& st) {
    vis[node] = 1;

    for (int nxt : adj[node]) {
        if (!vis[nxt]) 
            dfs(nxt, adj, vis, st);
    }

    // push AFTER exploring children
    st.push(node);
}

vector<int> topoSortDFS(vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> vis(n, 0);
    stack<int> st;
    
    for (int node = 0; node < n; node++) {
        if (!vis[node])
            dfs(node, adj, vis, st);
    }

    vector<int> res;
    while (!st.empty()) {
        res.push_back(st.top());
        st.pop();
    }
    return res;
}


void addEdge(vector<vector<int>>& adj, int u, int v) {
    adj[u].push_back(v);
}

int main() {
    int n =6;
    vector<vector<int>> adj(n); // adjacency list
    
    addEdge(adj, 0, 1);
    addEdge(adj, 1, 2);
    addEdge(adj, 2, 3);
    addEdge(adj, 4, 5);
    addEdge(adj, 3, 4);
    addEdge(adj, 5, 2);
    addEdge(adj, 5, 6);

    vector<int> res = topoSortDFS(adj);
    for (int vertex : res)
        cout << vertex << " ";
    cout << endl;
}
