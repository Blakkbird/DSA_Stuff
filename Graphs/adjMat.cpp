#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N, M; // nodes, num of edges
    if (!(cin >> N >> M)) return 0;

    vector<vector<int>> adj(N, vector<int>(N, 0));

    // Read M edges
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        
        // Convert 1-based input to 0-based index, optional
        // u--; v--;

        // Set edge (1 for unweighted)
        adj[u][v] = 1;
        adj[v][u] = 1; // Comment this out for directed graph
    }

    // Print the matrix
    cout << "Adjacency Matrix:" << endl;
    cout << "    ";
    for(int i=0;i<N;i++)
        cout << i << " ";
    cout << endl;
    for (int i = 0; i < N; ++i) {
        cout << i << " : " ;
        for (int j = 0; j < N; ++j) {
            cout << adj[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}