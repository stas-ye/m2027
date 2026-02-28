#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
using namespace std;

void construct_vector(vector<pair<int, int>>& v) {
    int z;
    cin >> z;
    for (int i = 0; i < z; i++) {
        int x, y;
        cin >> x >> y;
        v.push_back({x, y});
    }
}

bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
    return a.first < b.first;
}

class Graph {
    vector<vector<int>> adj;
    int size;
    vector<pair<int, int>> bridges;
    vector<bool> visited;
    vector<int> minimal_depth, height, artpoints;

    void dfs(int v, int p = -1) {
        visited[v] = true;
        minimal_depth[v] = height[v] = (p == -1 ? 0 : height[p] + 1);
        int desc = 0;
        for (auto i : adj[v]) {
            if (i == p) {
                continue;
            }
            if (visited[i]) {
                minimal_depth[v] = min(minimal_depth[v], height[i]);
            }
            else {
                dfs(i, v);
                minimal_depth[v] = min(minimal_depth[v], minimal_depth[i]);
                if (minimal_depth[i] > height[v]) {
                    if (i > v) {
                        bridges.push_back({v, i});
                    }
                    else {
                        bridges.push_back({i, v});
                    }
                }
                if (minimal_depth[i] >= height[v] && p != -1) {
                    artpoints.push_back(v);
                }
                desc += 1;
            }
        }
        if (desc > 1 && p == -1) {
            artpoints.push_back(v);
        }
    }

    public:
    Graph(int sz) {
        size = sz + 1;
        adj.resize(size);
        visited.resize(size);
        minimal_depth.resize(size);
        height.resize(size);
    }

    Graph(const vector<pair<int, int>>& edges, int sz) {
        size = sz + 1;
        adj.resize(size);
        visited.resize(size);
        minimal_depth.resize(size);
        height.resize(size);
        for (auto i : edges) {
            adj[i.first].push_back(i.second);
            adj[i.second].push_back(i.first);
        }
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void solve() {
        print();
        cout << endl;
        dfs(1);
        sort(bridges.begin(), bridges.end(), cmp);
        cout << "Bridges: ";
        for (int i = 0; i < bridges.size(); i++) {
            cout << "(" << bridges[i].first << ", " << bridges[i].second << ") ";
        }
        cout << endl;
        sort(artpoints.begin(), artpoints.end());
        cout << "Articulation points: ";
        set<int> ans;
        for (int i = 0; i < artpoints.size(); i++) {
            ans.insert(artpoints[i]);
        }
        for (auto i : ans) {
            cout << i << " ";
        }
    }

    void print() {
        for (int i = 1; i < adj.size(); i++) {
            cout << i << ": ";
            for (auto j : adj[i]) {
                cout << j << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    //int sz;
    //cin >> sz;
    //vector<pair<int, int>> bridges;
    //construct_vector(bridges);
//    Graph g(bridges, sz);
    Graph g(6);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(1, 3);
    g.addEdge(4, 6);
    g.addEdge(5, 6);
    
	g.solve();
    return 0;
}
