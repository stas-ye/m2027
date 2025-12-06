#include <iostream>
#include <vector>
#include <string>

std::vector<int> computePrefixFunction(const std::string& s) {
    int n = s.length();
    std::vector<int> pi(n, 0);
    
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        
        if (s[i] == s[j]) {
            j++;
        }
        
        pi[i] = j;
    }
    
    return pi;
}

std::vector<int> KMP_search(const std::string& text, const std::string& substring) {
    std::vector<int> result;
    if (substring.empty()) {
        return result;
    }
    std::vector<int> pi = computePrefixFunction(substring);
    int n = text.length();
    int m = substring.length();
    int j = 0;
    
    for (int i = 0; i < n; i++) {
        while (j > 0 && text[i] != substring[j]) {
            j = pi[j - 1];
        }
        if (text[i] == substring[j]) {
            j++;
        }
        if (j == m) {
            result.push_back(i - m + 1);
            j = pi[j - 1];
        }
    }
    
    return result;
}

void demonstratePrefixFunction(const std::string& s) {
    std::cout << "строка: " << s << std::endl;
    std::vector<int> pi = computePrefixFunction(s);
    
    std::cout << "Префикс-функция: ";
    for (int i = 0; i < pi.size(); i++) {
        std::cout << pi[i] << "  ";
    }
    std::cout << std::endl;
}

void demonstrateKMP(const std::string& text, const std::string& substring) {
    std::cout << "строка: " << text << std::endl;
    std::cout << "подстрока: " << substring << std::endl;
    
    std::vector<int> positions = KMP_search(text, substring);
    
    if (positions.empty()) {
        std::cout << "подстроки нет" << std::endl;
    } else {
        std::cout << "подстрока есть, начало на ";
        for (int pos : positions) {
            std::cout << pos << " ";
        }
    }
    
    std::cout << std::endl;
}

int main() {
    demonstratePrefixFunction("ababcabab");
    demonstratePrefixFunction("aaaaa");
    demonstratePrefixFunction("abcabcd");
    demonstrateKMP("ababcabababcababc", "ababc");
    demonstrateKMP("hello world, hello everyone", "hello");
    demonstrateKMP("abcabcabc", "abc");
    demonstrateKMP("abcdefg", "xyz");
    return 0;
}
