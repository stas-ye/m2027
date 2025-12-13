#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void levenshtein(vector <char>& s1, vector <char>& s2) {
	long long m = s1.size(), n = s2.size();
	vector <vector <long long>> matrix(m, vector <long long>(n));
	for (long long i = 0; i < n; i++) {
	    matrix[0][i] = i;
	}
	for (long long i = 0; i < m; i++) {
	    matrix[i][0] = i;
	}
	for (long long i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (s1[i] == s2[j]) {
                matrix[i][j] = min(matrix[i - 1][j - 1], min(matrix[i - 1][j] + 1, matrix[i][j - 1] + 1));
            } else {
                matrix[i][j] = min(matrix[i - 1][j - 1], min(matrix[i - 1][j], matrix[i][j - 1])) + 1;
            }
        }
	}
	cout << matrix[m - 1][n - 1] << endl << endl;
	int i = m - 1, j = n - 1, mi;
	while ((i > 0 && j > 0) || (i == 0 && j > 0) || (i > 0 && j == 0)) {
	    mi = min(matrix[i - 1][j - 1], min(matrix[i - 1][j], matrix[i][j - 1]));
	    if (i == 0) {
            cout << "INSERT " << s2[j] << " (" << j << ")" << endl;
            j--;
	    } else if (j == 0) {
            cout << "DELETE " << s1[i] << " (" << i << ")" << endl;
            i--;
	    } else {
            if (matrix[i - 1][j - 1] == mi && s1[i] != s2[j]) {
                cout << "REPLACE " << s1[i] << " (" << i << ") to " << s2[j] << " (" << j << ")" << endl;
                i--;
                j--;
            } else if (matrix[i - 1][j - 1] == mi && s1[i] == s2[j]) {
                i--;
                j--;
            } else if (matrix[i][j - 1] == mi) {
                cout << "INSERT " << s2[j] << " (" << j << ")" << endl;
                j--;
            } else if (matrix[i - 1][j] == mi) {
                cout << "DELETE " << s1[i] << " (" << i << ")" << endl;
                i--;
            }
	    }
	}
	return;
}

int main()
{
	string a, b;
	cin >> a >> b;
	vector<char> s1;
	vector<char> s2;
	s1.push_back('0');
	s2.push_back('0');
	for (int i = 0; i < a.size(); i++) {
		s1.push_back(a[i]);
	}
	for (int i = 0; i < b.size(); i++) {
		s2.push_back(b[i]);
	}
	levenshtein(s1, s2);
	return 0;
}
