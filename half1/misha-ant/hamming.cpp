#include <bits/stdc++.h>
using namespace std;
using ll = long long;


vector<bool> encode(vector<bool> a) {
    int n = a.size();
    int lg = 0;

    for (;;lg++) {
        if (n + lg < (1 << lg))
            break;
    }

    int m = n + lg;
    vector<bool> nw(m + 1, 0);
    int j = 1;
    int cnt = 1;

    for (int i = 1; i <= m; i++) {
        if (i == j) {
            j <<= 1;
            cnt++;
        } else {    
            nw[i] = a[i - cnt];
        }
    }

    for (int i = 1; i <= m; i <<= 1) {
        for (int j = i; j <= m; j += 2 * i) {
            for (int k = j; k <= min(j + i - 1, m); k++) {
                nw[i] = nw[i] ^ nw[k];
            }
        } 
    }

    nw.erase(nw.begin());
    return nw;
}


vector<bool> decode(vector<bool> a) {
    int m = a.size();
    int n = m;

    for (;;n--) {
        if (m < 1 << (m - n))
            break;
    }

    a.insert(a.begin(), 0);
    int sumMismatch = 0;

    for (int i = 1; i <= m; i <<= 1) {
        bool controlBit = a[i];
        for (int j = i; j <= m; j += 2 * i) {
            for (int k = j; k <= min(j + i - 1, m); k++) {
                controlBit = controlBit ^ a[k];
            }
        } 
        if (controlBit != a[i]) {
            sumMismatch += i;
        }
    }

    a[sumMismatch] = !a[sumMismatch];
    int j = 1;
    int cnt = 1;
    vector<bool> res(n);

    for (int i = 1; i <= m; i++) {
        if (i == j) {
            j <<= 1;
            cnt++;
        } else {    
            res[i - cnt] = a[i];
        }
    }

    return res;
}


bool test() {
    srand(17952);
    const int minN = 30;
    const int maxN = 50;

    int n = (rand() % (maxN - minN + 1)) + minN;
    vector<bool> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 2;
    }

    vector<bool> encoded = encode(a);
    int err = rand() % encoded.size();
    encoded[err] = !encoded[err];
    vector<bool> decoded = decode(encoded);

    if (decoded != a) {
        cout << "ERR" << endl;
        cout << n << endl;
        for (bool i: a)
            cout << i;
        cout << endl;
        cout << err << endl;
        return 1;
    }
    cout << "PASSED" << endl;

    return 0;
}


void stress(int cnt) {
    while (cnt--) {
        if(test()) {
            return;
        }
    }
}


int main() {
    //stress(100);
#ifdef LOCAL  
    freopen("/home/m/m/codes/input", "r", stdin);
    freopen("/home/m/m/codes/output", "w", stdout);
#else
    ios::sync_with_stdio(0);
    cin.tie(0);
#endif
    int t;
    cin >> t;
    int n;
    cin >> n;
    vector<bool> a(n);

    for (int i = 0; i < n; i++) {
        char x;
        cin >> x;
        a[i] = (x - '0');
    }

    if (t == 1) {
        for (bool i: encode(a))
            cout << i;
    } else {
        for (bool i: decode(a))
            cout << i;
    }
    cout << endl;
}
