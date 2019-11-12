#include <iostream>
#include <vector>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

const int MAX_N = 70000;
const int MAX_K = 1000;

vvi mat;

int comb(int n, int k) {

	int *val = &mat[n][k];

	if (*val != -1)
		return *val;

	if (k == 0 || k == n) {

		if (n < MAX_N && k < MAX_K)
			*val = 1;

		return 1;

	}

	if (k == 1 || k == n - 1) {

		if (n < MAX_N && k < MAX_K)
			*val = n;

		return n;

	}

	return *val = comb(n - 1, k - 1) + comb(n - 1, k);

}

bool resuelve() {

	int n, k;

	cin >> n >> k;

	if (n == 0 && k == 0)
		return false;

	cout << comb(n, k) << '\n';

	return true;

}

int main() {

	vi initial;

	initial.assign(MAX_K, -1);

	mat.assign(MAX_N, initial);

	while (resuelve());

	return 0;

}
