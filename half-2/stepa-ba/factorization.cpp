#include <vector>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,sse")
#include <bits/stdc++.h>
using ll = long long;
using namespace std;



void stupid(int x) {
    for (int i = 2; i*i <= x; i++) {
        while (x%i == 0) {
            cout << i << ' ';
            x/=i;
        }
    }
    if (x!=1) {
        cout << x << ' ';
    }
    cout << endl;
}



void sieve(int n) {
    vector<int> primes;
    vector<int> s(n+1, -1);
    primes.push_back(2);
    s[2] = 2;
    for (ll i = 2; i <= n; i++) {
        if (s[i] == -1) {
            primes.push_back(i);
            s[i] = i;
        }
        for (int x = 0; x < primes.size(); x++) {
            int p = primes[x];
            if (p > s[i] or i * p > n) {
                break;
            }
            s[i*p] = p;
        }
    }
    vector<vector<int>> res(n+1);
    for (int i = 2; i <= n; i++) {
        int j = i;
        while (true) {
            if (s[j] == -1) break;
            res[i].push_back(s[j]);
            j /= s[j]; 
        }
    }
    for (auto x:res) {
        for (auto y:x) {
            cout << y << ' ';
        }
        cout << endl;
    }
}



__int128 gcd(__int128 a, __int128 b) {
    if (a == 0) {
        return b;
    }
    if (b == 0) {
        return a;
    }
    return gcd(b%a, a);
}
__int128 c = 1;
__int128 f(__int128 y, __int128 n) {
    return (y*y+c)%n;
}
__int128 abs(__int128 x, __int128 y) {
    return (x < y) ? y-x : x-y;
}
mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
vector<__int128> factorize(__int128 n) {
    if (n == 2) {
        return {n};
    }
    if (n%2 == 0) {
        vector<__int128> res = {2};
        for (auto x : factorize(n/2)) {
            res.push_back(x);
        }
        return res;
    }
    __int128 s = 100000+1;
    if (s > n) {
        s = n;
    }
    __int128 x = 1;
    __int128 y = 1;
    c = rnd() % (n-1)+1;
    for (int i = 0; i < 10*s; i++) {
        x = f(x, n);
        y = f(f(y, n), n);
        __int128 gc = gcd(abs(x, y), n);
        if (gc != 1 && gc != n) {
            auto p1 = factorize(gc);
            auto p2 = factorize(n/gc);
            for (auto x : p2) {
                p1.push_back(x);
            }
            return p1;
        }
        if (i%s == s-1) {
            c = rnd() % (n-1)+1;
        }
    }
    return {n};
}


int main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#else
    cin.tie(nullptr);
    ios::sync_with_stdio(0);
#endif
    sieve(20);
    stupid(998244352);
    for (auto x:factorize(998244352)) {
        cout << (ll)x << ' ';
    }
    cout << endl;
    return 0;
}
