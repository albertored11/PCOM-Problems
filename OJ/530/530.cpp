#include <iostream>
#include <vector>

using namespace std;

bool resuelve() {

	long long int n, k;

	cin >> n >> k;

	if (n == 0 && k == 0)
		return false;

	long long int res = 1;
	long long int a, b;

	if (k >= (n + 1) / 2) {
        a = k + 1;
        b = n - k;
    }
	else {
        a = n - k + 1;
        b = k;
    }

    for (long long int i = 1; i <= b; ++i) {
        res *= a;
        res /= i;
        ++a;
    }

    cout << res << '\n';

	return true;

}

int main() {

	while (resuelve());

	return 0;

}
