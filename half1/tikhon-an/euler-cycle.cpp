#include <bits/stdc++.h>

using namespace std;

vector<set<int>> g;
vector<bool>used;

void dfs(int v){
    used[v] = 1;
    for (auto to : g[v]){
        if(!used[to]){
            dfs(to);
        }
    }
}

void euler(int v) {
    while (!g[v].empty()) {
        int u = *g[v].begin();
        g[v].erase(u);
        g[u].erase(v);
        euler(u);
    }
    cout << v + 1 <<  " ";
}

int main() {
    int n, m, a, b;
    cin >> n >> m;
    g.resize(n);
    used.resize(n);
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        g[a-1].insert(b-1);
        g[b-1].insert(a-1);
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (g[i].size() % 2 != 0) {
            throw invalid_argument("There is no Euler cycle here.");
        }
        if (!used[i]) {
            cnt += 1;
            dfs(i);
        }
    }
    if (cnt > 1) {
        throw invalid_argument("There is no Euler cycle here, this graph is disconnected");
    } else {
        euler(0);
    }

}
//test 1
//    7 9
//    1 6
//    1 5
//    7 2
//    7 6
//    2 3
//    2 4
//    5 4
//    6 3
//    2 6
//test 2
//    10 12
//    1 5
//    5 4
//    4 3
//    3 2
//    2 5
//    5 6
//    6 9
//    6 10
//    6 7
//    7 8
//    8 10
//    1 9
//test 3
//    10 11
//    1 5
//    5 4
//    4 3
//    3 2
//    2 5
//    5 6
//    6 9
//    6 10
//    6 7
//    7 8
//    8 10
//test 4
//    10 10
//    1 5
//    5 4
//    4 3
//    3 2
//    2 5
//    6 9
//    6 10
//    6 7
//    7 8
//    8 10
