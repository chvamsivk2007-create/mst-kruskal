#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class DSU {
    vector<int> parent, rank_;

public:
    DSU(int n) {
        parent.resize(n);
        rank_.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); 
        return parent[x];
    }

    bool unite(int x, int y) {
        int rootX = find(x), rootY = find(y);
        if (rootX == rootY) return false; 

        if (rank_[rootX] < rank_[rootY]) swap(rootX, rootY);
        parent[rootY] = rootX;
        if (rank_[rootX] == rank_[rootY]) rank_[rootX]++;
        return true;
    }
};

struct Edge {
    int u, v, weight;
};

bool compareEdge(Edge a, Edge b) {
    return a.weight < b.weight;
}

int main() {
    int n, e;
    cout << "Enter number of vertices: ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> e;

    vector<Edge> edges(e);
    cout << "Enter edges as: u v weight\n";
    for (int i = 0; i < e; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    sort(edges.begin(), edges.end(), compareEdge);

    DSU dsu(n);
    int mstWeight = 0;

    cout << "Edges in MST:\n";
    for (auto &edge : edges) {
        if (dsu.unite(edge.u, edge.v)) {
            mstWeight += edge.weight;
            cout << edge.u << " - " << edge.v << " : " << edge.weight << endl;
        }
    }

    cout << "Total weight of MST: " << mstWeight << endl;

    return 0;
}
