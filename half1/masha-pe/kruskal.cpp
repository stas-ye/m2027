#include <bits/stdc++.h>

using namespace std;

struct Edje {
    int u, v, w;

    Edje() {}

    Edje(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
};

bool cmp(Edje& a, Edje& b) {
    return a.w < b.w;
}

struct DSU {
    vector<int> p, sz;

    DSU(int n) {
        p.resize(n);
        sz.resize(n);
        for (int i = 0; i < n; i++) p[i] = i, sz[i] = 1;
    }

    int get(int v) {
        return (v == p[v]) ? v : get(p[v]);
    }

    bool unite(int u, int v) {
        u = get(u), v = get(v);
        if (u == v) return false;
        if (sz[v] > sz[u]) swap(u, v);
        sz[u] += sz[v];
        p[v] = u;
        return true;
    }

    long long kruskal(vector<Edje>& g) {
        sort(g.begin(), g.end(), cmp);
        long long min_cost = 0;
        for (auto& [u, v, w] : g) {
            min_cost += unite(u, v) * w;
        }
        return min_cost;
    }
};

void solve() {
    int n, m; cin >> n >> m;
    vector<Edje> g;
    for (int i = 0; i < m; i++) {
        g.emplace_back();
        cin >> g[i].u >> g[i].v >> g[i].w;
        g[i].u--, g[i].v--;
    }
    DSU d(n);
    cout << d.kruskal(g) << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}

/*
4 4
1 2 1
2 3 2
3 4 5
4 1 4
*/

/*
7 10
1 2 3
1 4 4
1 6 3
2 5 5
2 6 3
3 4 2
3 5 2
3 7 4
4 6 5
5 7 3
*/
