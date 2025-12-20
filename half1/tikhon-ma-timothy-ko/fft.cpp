#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using comp = complex<ld>;

const ld PI = atan2(1, 0) * 2;

void fft(vector<comp>& p, comp wn) {
    ll n = p.size();
    if (n == 1) return;
    vector<comp> a(n / 2), b(n / 2);
    // делим массив пополам
    for (int i = 0; i < n / 2; i++) {
        a[i] = p[2 * i]; // коэффициенты при четных степенях
        b[i] = p[2 * i + 1]; // коэффициенты при нечетных степенях
    }
    // рекурсия
    // w(n/2) = wn * wn т.к e^(2pi*i/(n/2)) = e^(4pi*i/n)
    fft(a, wn * wn);
    fft(b, wn * wn);
    comp w = 1;
    for (int i = 0; i < n / 2; i++) {
        p[i] = a[i] + w * b[i];
        p[i + n / 2] = a[i] - w * b[i]; // т.к w^(i+n/2) = -w^i
        w *= wn;
    }
}

void fft_forward(vector<comp>& p) {
    fft(p, polar((ld)1, 2 * PI / p.size()));
}

void fft_backward(vector<comp>& p) {
    fft(p, polar((ld)1, -2 * PI / p.size()));
}


vector<ll> interpolate(vector<comp> p) {
    ll n = p.size();
    fft_backward(p);
    vector<ll> res(n);
    for(ll i = 0; i < n; i++) {
        res[i] = round(real(p[i]) / n);
    }
    return res;
}

vector<ll> multiply(const vector<ll>& a, const vector<ll>& b) {
    vector<comp> fa(a.begin(), a.end());
    vector<comp> fb(b.begin(), b.end());

    ll n = 1;
    while (n < a.size() + b.size() - 1) {
        n *= 2;
    }
    fa.resize(n);
    fb.resize(n);
    fft_forward(fa);
    fft_forward(fb);

    for (ll i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }
    vector<ll> res = interpolate(fa);
    return res;
}


void solve() {
    ll n;
    cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }
    ll m;
    cin >> m;
    vector<ll> b(m);
    for (ll i = 0; i < m; i++) {
        cin >> b[i];
    }
    vector<ll> res = multiply(a, b);
    for (ll i = 0; i < n + m - 1; i++) {
        cout << res[i] << ' ';
    }
}


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    solve();

    return 0;
}

