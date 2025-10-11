#include <bits/stdc++.h>

using num = std::string;
using long64 = long long;

long64 ctol(char x){
    long64 y = long64(x - '0');
    return y;
}

num addzeros(num& x, long64 n){
    while (x.size() < n){
        x = "0" + x;
    }
    return x;
}

num removezeros(num& x) {
    long64 i = 0;
    while (i < x.size() && x[i] == '0') {
        i += 1;
    }
    if (i == x.size()) return "0";
    return x.substr(i, x.size());
}

num add(const num& a, const num& b){
    num sum;
    long64 i = a.size() - 1, j = b.size() - 1, q = 0;
    while (i >= 0 && j >= 0){
        long64 ai = ctol(a[i]);
        long64 bj = ctol(b[j]);
        long64 r = (ai + bj + q) % 10;
        sum += std::to_string(r);
        q = (ai + bj + q) / 10;
        i -= 1;
        j -= 1;
    }
    if (i == -1 && j != -1){
        while (j >= 0){
            long64 bj = ctol(b[j]);
            long64 r = (bj + q) % 10;
            sum += std::to_string(r);
            q = (bj + q) / 10;
            j -= 1;
        }
    }
    else if (i != -1 && j == -1){
        while (i >= 0){
            long64 ai = ctol(a[i]);
            long64 r = (ai + q) % 10;
            sum += std::to_string(r);
            q = (ai + q) / 10;
            i -= 1;
        }
    }
    if (q == 1){
        sum += std::to_string(q);
    }
    std::reverse(sum.begin(), sum.end());
    return sum;
}

num subtract(const num& ac, const num& b){
    num a = ac;
    num diff;
    long64 i = a.size() - 1, j = b.size() - 1;
    while (j >= 0){
        if (a[i] < b[j]){
            if (a[i - 1] > '0'){
                a[i - 1] -= 1;
                a[i] += 10;
            }
            else{
                long64 k = i - 1;
                while (a[k] == '0'){
                    a[k] += 9;
                    k -= 1;
                }
                a[k] -= 1;
                a[i] += 10;
            }
        }
        diff += std::to_string(a[i] - b[j]);
        i -= 1;
        j -= 1;
    }
    while (i >= 0){
        diff += a[i];
        i -= 1;
    }
    std::reverse(diff.begin(), diff.end());
    return removezeros(diff);
}

num karatsuba(num& x, num& y) {
    if (x == "0" || y == "0") return "0";
    if (x.size() == 1 && y.size() == 1) {
        long64 product = std::stoi(x) * std::stoi(y);
        return std::to_string(product);
    }
    long64 n = std::max(x.size(), y.size());
    n += (n % 2);
    x = addzeros(x, n);
    y = addzeros(y, n);
    long64 m = n / 2;
    num xl = x.substr(0, m);
    num xr = x.substr(m, n);
    num yl = y.substr(0, m);
    num yr = y.substr(m, n);
    num z1 = karatsuba(xl, yl);
    num z2 = karatsuba(xr, yr);
    num xlr = add(xl, xr);
    num ylr = add(yl, yr);
    num z3 = karatsuba(xlr, ylr);
    num z4 = subtract(subtract(z3, z1), z2);
    num lh = z1 + num(n, '0');
    num rh = z4 + num(m, '0');
    num result = add(add(lh, rh), z2);
    return removezeros(result);
}

int main() {
    num x, y;
    std::cin >> x >> y;
    num res = karatsuba(x, y);
    std::cout << res << std::endl;
    return 0;
}
