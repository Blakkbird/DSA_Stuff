#include <bits/stdc++.h>
using namespace std;

struct edgei {
    int u, v, wt;
};

class DSU {
    vector<int> parent, rankv;
public:
    DSU(int n) {
        parent.resize(n);
        rankv.resize(n, 0);
        for(int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if(parent[x] == x)
            return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int x, int y) {
        int r1 = find(x), r2 = find(y);
        if(r1 != r2) {
            // union by rank
            if(rankv[r1] < rankv[r2]) {
                parent[r1] = r2;
            } 
            else if(rankv[r2] < rankv[r1]) {
                parent[r2] = r1;
            } 
            else {
                parent[r2] = r1;
                rankv[r1]++;
            }
        }
    }
};

int mstWt = 0;

vector<edgei> kruskal(int n, vector<edgei>& edges) {
    sort(edges.begin(), edges.end(),
        [](const edgei &e1, const edgei &e2) {
            return e1.wt < e2.wt;
        }
    );

    DSU dsu(n);
    vector<edgei> mstEdges;  // store mst edges
    mstWt = 0;

    for(auto &ed : edges) {
        if(dsu.find(ed.u) != dsu.find(ed.v)) {
            dsu.unite(ed.u, ed.v);
            mstWt += ed.wt;
            mstEdges.push_back(ed);
            if(mstEdges.size() == n - 1)
                break;
        }
    }
    return mstEdges;
}

int main() {
    int n = 4;
    vector<edgei> edges = {
        {0,1,10}, {1,2,15}, {0,2,5},
        {2,3,4}, {1,3,6}
    };

    vector<edgei> mst = kruskal(n, edges);

    cout << "MST Weight = " << mstWt << "\n";
    cout << "Edges in MST:\n";
    for(auto &e : mst)
        cout << e.u << " -- " << e.v << " (" << e.wt << ")\n";

    return 0;
}
