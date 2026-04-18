#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


vector<int> matching; // matching[u] -  с кем в паре u из право доли
vector<bool> used;

bool dfs(int v, vector<vector<int>>& g){
    for (int u: g[v]){
        if (!used[u]){
            used[u] = true;
            if (matching[u] == -1 || dfs(matching[u], g)){
                matching[u] = v;
                return true;
            }
        }
    }
    return false;
}


vector<pair<int, int>> FindMatching(int& n, int& m, vector<vector<int>>& left_v) {
    used.resize(n + m +1, 0);
    matching.resize(n + m + 1, -1);
    int count_matching = 0;
    for (int v = 0; v < n; v++) {
        fill(used.begin(), used.end(), 0);
        if (dfs(v, left_v)) {
            count_matching++;
        }
    }
    vector<pair<int, int>> max_matching;
    for (int u = n; u < n + m; u++) {
        if (matching[u] != -1){
            max_matching.push_back({matching[u] +1, u+1});
        }
    }
    sort(max_matching.begin(), max_matching.end());
    return max_matching;
}


struct TestCase {
    int n; //кол-во ребер в левой доле
    int m; //кол-во ребер в право доле
    vector<vector<int>> graph;
    vector<pair<int, int>> expected_result;
};

void TestGetMaxMatching() {
    vector<TestCase> test_cases {
        
        {5, 5, {{5, 6}, {5, 8}, {6, 9}, {7, 8}, {9}}, {{1, 6}, {2, 9}, {3, 7}, {4, 8},{5, 10}}},
        {3, 2, {{3}, {3, 4}, {4}}, {{1, 4}, {2, 5}}},
        
    };
    for (auto test_case : test_cases) {
        vector<pair<int, int>> check = FindMatching(test_case.n,  test_case.m, test_case.graph);
        if (check != test_case.expected_result) {
            cout << "Error" << endl;
        }else {
            for (int i= 0 ; i < check.size(); i++) {
                cout << check[i].first << " " << check[i].second << endl;
            }
            cout << endl;
        }
    }
}


int main(){
    TestGetMaxMatching();
}
