#include <bits/stdc++.h>
#pragma GCC optimize("O3,Ofast,unroll-loops,fast-math")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#define ll long long
#define ld long double
using namespace std;
vector<ll> a;
vector<ll> t;
void build(int v, int l, int r) {
    if (r - l == 1) {
        t[v] = a[l];
        return;
    }
    int m = (r+l)/2;
    build(2*v+1, l, m); // building the left subtree
    build(2*v+2, m, r); // bulding the right subtree
    t[v] = t[2*v+1] + t[2*v+2];
}
ll query(int v, int l, int r, int ql, int qr) {
    if (qr<=l or r<=ql) { // fully outside
        return 0;
    }
    if (ql<=l and r<=qr) { // fully inside
        return t[v];
    }
    int m = (r+l)/2;
    return query(2*v+1, l, m, ql, qr) + query(2*v+2, m, r, ql, qr);
}
void change(int v, int l, int r, int i, int x) {
    if (r-l == 1) {
        t[v] = x;
        return;
    }
    int m = (r+l)/2;
    if (i < m) {
        change(2*v+1, l, m, i, x); // changing the left subtree
    } else {
        change(2*v+2, m, r, i, x); // changing the right subtree
    }
    t[v] = t[2*v+1] + t[2*v+2];
}
int main() {
#ifdef LOCAL
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#else
    cin.tie(nullptr);
    ios::sync_with_stdio(0);
#endif
    int n, q;
    cin >> n >> q;
    a.resize(n);
    t.resize(4*n);
    // input
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(0, 0, n);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) { // changing
            int i, x;
            cin >> i >> x;
            change(0, 0, n, i-1, x);
        } else { // query
            int l, r;
            cin >> l >> r;
            cout << query(0, 0, n, l-1, r) << '\n';
        }
    }
    return 0;
}
/* 
example test
5 3
1 2 3 4 5
2 1 5
1 2 3
2 1 5
*/
// meow meow meow meow meow
