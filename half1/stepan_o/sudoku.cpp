#include<iostream>
#include<vector>
#include<queue>
#include<cmath>
#include<stack>

void Print(const std::vector<std::vector<int>>& s) {
    for (int y = 0; y < s.size(); y++) {
        for (int x = 0; x < s[0].size(); x++) {
            std::cout << s[y][x];
        }
        std::cout << std::endl;
    }
}

class Sudoku {
private:
    int n;
    int n2;
    std::vector<std::vector<std::pair<int, int>>> rows;
    std::vector<std::vector<int>> columns;
    std::stack<int> s;
    
    void ExtractIntersects(int row) {
        for (std::pair<int, int> pr : rows[row]) {
            int elt = pr.first;
            columns[elt][n] += n;
            for (int k = 0; k < n; ++k) {
                if (columns[elt][k] != -1 && columns[elt][k] != row) {
                    for (std::pair<int, int> pr2 : rows[columns[elt][k]]) {
                        int other_elt = pr2.first,
                            index = pr2.second;
                        if (other_elt != elt && columns[other_elt][index] != -1) {
                            --columns[other_elt][n];
                            columns[other_elt][index] = -1;
                            
                        }
                    }
                }
            }
        }
    }
    
    void RestoreIntersects(int row) {
        for (int i = 3; i >= 0; --i) {
            int elt = rows[row][i].first;
            columns[elt][n] -= n;
            for (int k = 0; k < n; ++k) {
                if (columns[elt][k] != -1) {
                    for (std::pair<int, int> pr : rows[columns[elt][k]]) {
                        int col = pr.first,
                            index = pr.second;
                        columns[col][index] = columns[elt][k];
                    }
                }
            }
        }
    }
    
    bool AlgorithmX() {
        int mini = 0;
        for (int i = 1; i < columns.size(); ++i) {
            int siz = columns[i][n];
            if (siz < columns[mini][n]) {
                mini = i;
            }
        }
        if (columns[mini][n] > n) {
            return 1;
        } else if (columns[mini][n] > 0) {
            for (int i = 0; i < n; ++i) {
                int canditate = columns[mini][i];
                if (canditate != -1) {
                    s.push(canditate);
                    ExtractIntersects(canditate);
                    if (AlgorithmX()) {
                        return 1;
                    }
                    RestoreIntersects(canditate);
                    s.pop();
                }
            }
        }
        return 0;
    }
    
    void PrintIndex(int x) {
        std::cout << x / (n * n) << ' ' << (x % (n * n)) / n << ' ' << x % n + 1 << std::endl;
    }
    
    int Index(int x1, int x2, int x3) {
        return x1 * n * n + x2 * n + x3;
    }
public:
    Sudoku(std::vector<std::vector<int>> puzzle)
        : n(puzzle[0].size())
        , n2(sqrt(n))
        , rows(n * n * n, std::vector<std::pair<int, int>> (4))
        , columns(4 * n * n, std::vector<int> (n + 1))
        , s()
    {
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                for (int num = 0; num < n; num++) {
                    rows[Index(row, col, num)][0].first = Index(0, row, col);
                    rows[Index(row, col, num)][0].second = num;
                    rows[Index(row, col, num)][1].first = Index(1, row, num);
                    rows[Index(row, col, num)][1].second = col;
                    rows[Index(row, col, num)][2].first = Index(2, col, num);
                    rows[Index(row, col, num)][2].second = row;
                    rows[Index(row, col, num)][3].first = Index(3, (row / n2) * n2 + col / n2, num);
                    rows[Index(row, col, num)][3].second = row % n2 + (col % n2) * n2;
                }
            }
        }
        //type:
        //0 - в клетке (k, l) есть число
        //1 - в строке k есть число l
        //2 - в столбце k есть число l
        //3 - в квадрате k есть число l
        for (int k = 0; k < n; k++) {
            for (int l = 0; l < n; l++) {
                columns[Index(0, k, l)][n] = n;
                columns[Index(1, k, l)][n] = n;
                columns[Index(2, k, l)][n] = n;
                columns[Index(3, k, l)][n] = n;
                for (int i = 0; i < n; ++i) {
                    columns[Index(0, k, l)][i] = Index(k, l, i);
                    columns[Index(1, k, l)][i] = Index(k, i, l);
                    columns[Index(2, k, l)][i] = Index(i, k, l);
                    columns[Index(3, k, l)][i] = Index((k / n2) * n2 + i % n2, (k % n2) * n2 + i / n2, l);
                }
            }
        }
        for (int y = 0; y < 9; y++) {
            for (int x = 0; x < 9; x++) {
                if (puzzle[y][x] != 0) {
                    int row = Index(y, x, puzzle[y][x] - 1);
                    s.push(row);
                    ExtractIntersects(row);
                }
            }
        }
    };
    
    std::vector<std::vector<int>> Solve() {
        if (!AlgorithmX()) {
            //throw std::runtime_error("no solution");
            std::cout << "no solution";
            return std::vector<std::vector<int>>();
        }
        std::vector<std::vector<int>> result(n, std::vector<int> (n));
        while (!s.empty()) {
            int index = s.top();
            s.pop();
            result[index / (n * n)][(index % (n * n)) / n] = index % n + 1;
        }
        return result;
    }
};

int main() {
    Sudoku s({
        {0, 0, 4, 0, 0, 3, 7, 0, 0},
        {9, 0, 0, 8, 2, 0, 0, 0, 6},
        {0, 0, 7, 0, 0, 0, 9, 0, 0},
        {6, 0, 0, 0, 0, 0, 0, 8, 0},
        {0, 1, 0, 0, 3, 0, 0, 2, 0},
        {0, 9, 0, 0, 0, 0, 0, 0, 5},
        {0, 0, 9, 0, 0, 0, 1, 0, 0},
        {1, 0, 0, 0, 4, 2, 0, 0, 3},
        {0, 0, 8, 5, 0, 0, 2, 0, 0}
    });
    Print(s.Solve());
    return 0;
}
