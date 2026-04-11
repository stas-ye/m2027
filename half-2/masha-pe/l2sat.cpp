#include <bits/stdc++.h>

using namespace std;

vector<set<int>> g, g_rev;
vector<int> color, used, ord;

void dfs(int v) {
    used[v] = 1;
    for (auto to : g[v]) {
        if (!used[to]) {
            dfs(to);
        }
    }
    ord.push_back(v);
}

void dfs_paint(int v, int c) {
    used[v] = 1;
    color[v] = c;
    for (auto to : g_rev[v]) {
        if (!used[to]) {
            dfs_paint(to, c);
        }
    }
}

void kss(int n) {
    color.clear(), color.resize(n);
    used.clear(), used.resize(n);
    ord.clear();
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i);
        }
    }
    reverse(ord.begin(), ord.end());
    used.clear(), used.resize(n);
    int c = 1;
    for (auto i : ord) {
        if (!used[i]) dfs_paint(i, c++);
    }
}

void solve() {
    int n, m; cin >> n >> m;
    g.clear(), g.resize(2 * n);
    g_rev.clear(), g_rev.resize(2 * n);

    for (int it = 0; it < m; it++) {
        int i1, e1, i2, e2; cin >> i1 >> e1 >> i2 >> e2; i1--; i2--;
        //(i1 == e1) ^ (i2 == e2)

        if (e1 && e2) {
            g[i1 + n].emplace(i2);
            g[i2 + n].emplace(i1);
            g_rev[i1].emplace(i2 + n);
            g_rev[i2].emplace(i1 + n);
        }
        if (e1 && !e2 && i1 != i2) {
            g[i1 + n].emplace(i2 + n);
            g[i2].emplace(i1);
            g_rev[i2 + n].emplace(i1 + n);
            g_rev[i1].emplace(i2);
        }
        if (!e1 && e2 && i1 != i2) {
            g[i2 + n].emplace(i1 + n);
            g[i1].emplace(i2);
            g_rev[i1 + n].emplace(i2 + n);
            g_rev[i2].emplace(i1);
        }
        if (!e1 && !e2) {
            g[i1].emplace(i2 + n);
            g[i2].emplace(i1 + n);
            g_rev[i1 + n].emplace(i2);
            g_rev[i2 + n].emplace(i1);
        }
    }
    kss(2 * n);
    vector<int> x;
    for (int i = 0; i < n; i++) {
        if (color[i] == color[n + i]) {
            cout << -1 << '\n';
            return;
        }
        if (color[i] > color[i + n]) {
            x.emplace_back(1);
        } else {
            x.emplace_back(0);
        }
    }
    for (auto i : x) cout << i << ' ';
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
