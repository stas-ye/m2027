#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<int, int>>> g;
const int INF = 1e9;

long long prima_slow(int n) {
    vector<int> min_e(n, INF);
    min_e[0] = -1;
    for (auto [to, w] : g[0]) {
        min_e[to] = min(min_e[to], w);
    }
    long long min_cost = 0;
    for (int it = 0; it < n - 1; it++) {
        int v = -1;
        for (int i = 0; i < n; i++) {
            if (min_e[i] != -1 && (v == -1 || min_e[i] < min_e[v])) v = i;
        }
        min_cost += min_e[v];
        min_e[v] = -1;
        for (auto [to, w] : g[v]) {
            min_e[to] = min(min_e[to], w);
        }
    }
    return min_cost;
}

long long prima_fast(int n) {
    vector<int> min_e(n, INF);
    set<pair<int, int>> s;
    min_e[0] = 0;
    for (int i = 0; i < n; i++) {
        s.emplace(min_e[i], i);
    }
    long long min_cost = 0;
    while (!s.empty()) {
        auto v = s.begin()->second;
        min_cost += min_e[v];
        min_e[v] = -1;
        s.erase(s.begin());
        for (auto [to, w] : g[v]) {
            if (min_e[to] != -1 && min_e[to] > w) {
                s.erase({min_e[to], to});
                min_e[to] = w;
                s.emplace(min_e[to], to);
            }
        }
    }
    return min_cost;
}

void solve() {
    int n, m; cin >> n >> m;
    g.resize(n);
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w; u--, v--;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    cout << prima_slow(n) << '\n';
    cout << prima_fast(n) << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
