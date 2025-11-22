#include <iostream>
#include <vector>


using namespace std;


struct need {
    int from;
    int to;
    int weight;
};


vector<string> FindWay(int& n,  vector<vector<int>>& v){
    vector<need> graph(n);
    for (int i = 0; i < v.size(); i++) {
        graph[i].from = v[i][0] -1 ;
        graph[i].to = v[i][1] - 1;
        graph[i].weight = v[i][2];
    };
    //int INT_MAX = 2e9;
    vector<int> d(n, INT_MAX);
    d[0] = 0;
    
    for (int i = 0; i < n; i++) {
        for (auto el : graph) {
            if (d[el.from] != INT_MAX) {
                d[el.to] = min(d[el.to], d[el.from] + el.weight);
            }
        }
    }
    
    for (auto el : graph) {
        if (d[el.from] != INT_MAX and (d[el.from] + el.weight) < d[el.to]) {
            return {"Graph contains negative weight cycle"};
        }
    } 
    
    
    vector<string> ans;
    for (int i = 0; i < n;i++) {
        if (d[i] == INT_MAX) {
            ans.push_back("-");
        } else {
            ans.push_back(to_string(d[i]));
        }
    }
    return ans;
}





struct TestCase {
    int n;
    vector<vector<int>> graph;
    vector<string> expected_result;
};



void TestGetWay() {
    vector<TestCase> test_cases {
        {6,  {{1, 2, 10}, {2, 3, 10}, {1, 3, 100}, {4, 5, -10}}, {"0",  "10",  "20",  "-",  "-",  "-" }},
        {9, {{1, 3, 10}, {1, 4, 10}, {2, 7, 1}, {4, 2, 3}, {2, 8, -10}, {5, 7, 3}, {5, 8, -10}, {5, 7, 3}, {5, 8, -1}, {6, 1, 3}, {9, 3, 4}}, {"0", "13", "10", "10", "-", "-", "14", "3", "-"}},
        {3, {{2, 1, 100}, {1, 3, -51}, {3, 2, -50}}, {"Graph contains negative weight cycle"}}
    };
    for (auto test_case : test_cases) {
        vector<string> check = FindWay(test_case.n,  test_case.graph);
        if (check != test_case.expected_result) {
            cout << "Error" << endl;
        }else {
            for (int i= 0 ; i < check.size(); i++) {
                cout << check[i] << " ";
            }
            cout << endl;
        }
    }
}



int main() {
    TestGetWay();
}
