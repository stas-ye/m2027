#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int LongDeikstra(const int& n, const int& first, const int& last, const vector<vector<int>>& vec) {
    vector<int> used(n, false);
    vector<int> distance(n, 1e9);
    distance[first] = 0;
    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j) {
            if (!used[j]) {
                if (v == -1 || distance[j] < distance[v]) {
                    v = j;
                }
            }
        }
        if (v == -1) {
            break;
        }
        for (int j = 0; j < n; ++j) {
            if (vec[v][j] != -1) {
                distance[j] = min(distance[j], distance[v] + vec[v][j]);
            }
        }
        used[v] = true;
    }
    if (distance[last] == 1e9) {
        return -1;
    }
    return distance[last];
}

vector<int> FastDeikstra(const int& n, const vector<vector<pair<int, int>>>& vec, const int& f) {
    vector<bool> used(n, false);
    vector<int> dist(n, 1e9);
    dist[f] = 0;
    priority_queue <pair<int, int>> q;
    q.push({0, f});
    while (q.size() != 0) {
        int v = (q.top()).second;
        q.pop();
        if (used[v]) {
            continue;
        }
        used[v] = true;
        for (pair<int, int> u : vec[v]) {
            if (dist[u.first] > dist[v] + u.second) {
                dist[u.first] = dist[v] + u.second;
                q.push({-dist[u.first], u.first});
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (dist[i] == 1e9) {
            dist[i] = -1;
        }
    }
    return dist;
}

struct TestCaseForLongDeikstra {
    int n;
    int first;
    int last;
    vector<vector<int>> vec;
    int expected_result;
};

struct TestCaseForFastDeikstra {
    int n;
    vector<vector<pair<int, int>>> vec;
    int f;
    vector<int> expected_result;
};

void CheckLongDeikstra(const int& actual_result, const int& expected_result) {
    if (expected_result != actual_result) { 
        cout << "Error!" << endl;
    } else {
        cout << "OK" << endl;
    }
}

void CheckFastDeikstra(const vector<int>& actual_result, const vector<int>& expected_result) {
    if (expected_result != actual_result) { 
        cout << "Error!!!" << endl;
    } else {
        cout << "OK" << endl;
    }
}

void RunTests() { 
    vector<TestCaseForLongDeikstra> test_cases_for_long_deikstra{
        {3, 1, 0, {{0, 1, 1}, {4, 0, 1}, {2, 1, 0}}, 3},
        {3, 0, 1, {{0, -1, 2}, {3, 0, -1}, {-1, 4, 0}}, 6},
    };
    for (const TestCaseForLongDeikstra& elem : test_cases_for_long_deikstra) {
        CheckLongDeikstra(LongDeikstra(elem.n, elem.first, elem.last, elem.vec), elem.expected_result);
    }

    vector<TestCaseForFastDeikstra> test_cases_for_fast_deikstra{
        {4, {{{1, 5}}, {{0, 5}}, {{3, 2}}, {{2, 2}}}, 0, {0, 5, -1, -1}},
        {1, {{}}, 0, {0}},
    };
    for (const TestCaseForFastDeikstra& elem : test_cases_for_fast_deikstra) {
        CheckFastDeikstra(FastDeikstra(elem.n, elem.vec, elem.f), elem.expected_result);
    }
}

int main() {
    RunTests();
    return 0;
}
