#include <iostream>
#include <cstring>

using namespace std;

const int MAX = 40;

long long int pd[MAX + 1];

long long int boxes(int n) {

	if (n == 0 || n == 1)
		return 1;

	if (n == 2)
		return 5;

	if (n == 3)
		return 11;

	long long int *val = &pd[n];

	if (*val != -1)
		return *val;

	if (n % 2 == 0)
		return *val = boxes(n - 1) + boxes(n - 2) * 5 - 2 * boxes(n - 4) - 1;

	return *val = boxes(n - 1) + boxes(n - 2) * 5 - 2 * boxes(n - 4) + 1;

}

void resuelve() {

	int n;

	cin >> n;

	cout << boxes(n) << '\n';

}

int main() {

	int nCasos;

	memset(pd, -1, (MAX + 1) * sizeof(long long int));

	cin >> nCasos;

	while (nCasos--) resuelve();

	return 0;

}
