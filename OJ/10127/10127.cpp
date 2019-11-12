#include <iostream>

using namespace std;

bool resuelve() {

	int n;

	cin >> n;

	if (!cin)
		return false;

	int mul = 1;
	int numCifras = 1;

	while (mul < n) {
		mul *= 10;
		++mul;
		++numCifras;
	}

	while (mul % n != 0) {

		mul *= 10;
		++mul;
		++numCifras;

		while (mul < n) {
			mul *= 10;
			++mul;
			++numCifras;
		}

		mul %= n;

	}

	cout << numCifras << '\n';

	return true;

}

int main() {

	while (resuelve());

	return 0;

}
