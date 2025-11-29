#include <bits/stdc++.h>
using namespace std;

vector<int> prefixsum(const vector<int>& a) {
    int n = a.size();
    vector<int> prefix(n + 1);
    prefix[0] = 0;
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + a[i];
    }
    return prefix;
}

vector<int> prefixmultiply(const vector<int>& a) {
    int n = a.size();
    vector<int> prefix(n + 1);
    prefix[0] = 1;
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] * a[i];
    }
    return prefix;
}

vector<int> prefixxor(const vector<int>& a) {
    int n = a.size();
    vector<int> prefix(n + 1);
    prefix[0] = 0;
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] ^ a[i];
    }
    return prefix;
}

vector<int> prefixmin(const vector<int>& a) {
    int n = a.size();
    vector<int> prefix(n);
    prefix[0] = a[0];
    for (int i = 1; i < n; i++) {
        prefix[i] = min(prefix[i - 1], a[i]);
    }
    return prefix;
}

void otrezoksum(const vector<int>& v, int l, int r){
    cout << "На отрезке с " << l << " по " << r << ": " << v[r] - v[l - 1] << endl;
}

void otrezokmult(const vector<int>& v, int l, int r){
    cout << "На отрезке с " << l << " по " << r << ": " << v[r] / v[l - 1] << endl;
}

void otrezokxor(const vector<int>& v, int l, int r){
    cout << "На отрезке с " << l << " по " << r << ": " << (v[r] ^ v[l - 1]) << endl;
}

void print(const vector<int>& v){
    for (auto to: v){
        cout << to << " ";
    }
    cout << endl;
}

int main() {
    vector<int> a = {3, 7, 1, 4, 8, -2, 10};
    print(a);
    vector<int> prefsum = prefixsum(a);
    cout << "Сумма: ";
    print(prefsum);
    otrezoksum(prefsum, 2, 6);
    vector<int> prefmultiply = prefixmultiply(a);
    cout << "Произведение: ";
    print(prefmultiply);
    otrezokmult(prefmultiply, 2, 6);
    vector<int> prefxor = prefixxor(a);
    cout << "XOR: ";
    print(prefxor);
    otrezokxor(prefxor, 3, 5);
    vector<int> prefmin = prefixmin(a);
    cout << "Минимум: ";
    print(prefmin);
}
