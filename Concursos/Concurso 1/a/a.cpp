#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

int mat[30][30];

int fun(int i, int j) {

	if (mat[i][j] != -1)
		return mat[i][j];

	if (i == 1 || j == 1)
		return mat[i][j] = 1;

	if (i == 2)
		return mat[i][j] = j;

	if (j == 2)
		return mat[i][j] = i;

	return mat[i][j] = fun(i - 1, j) * 2;

}

void resuelve() {

	int f, c;

	cin >> f >> c;

	cout << fun(f, c) << '\n';

}

int main() {

	for (int i = 0; i < 30; ++i)
		for (int j = 0; j < 30; ++j)
			mat[i][j] = -1;

	int nCasos;

	cin >> nCasos;

	while (nCasos--) resuelve();

}
