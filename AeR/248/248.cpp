// Primera versión. Da MLE porque guarda los datos en memoria.

#include <iostream>
#include <queue>

using namespace std;

int mayorBeneficio(queue<int> &beneficios, int L) {

	int ret = 0;
	int beneficioActual = 0;

	while (!beneficios.empty()) {

		beneficioActual += beneficios.front();

		if (L > 0) {
			beneficios.push(beneficios.front());
			--L;
		}

		beneficios.pop();

		if (beneficioActual < 0)
			beneficioActual = 0;
		else if (beneficioActual > ret)
			ret = beneficioActual;

	}

	return ret;

}

bool testCase() {

	int L;

	cin >> L;

	if (L == 0)
		return false;

	queue<int> beneficios;

	for (int i = 0; i < L; ++i) {

		int b;

		cin >> b;

		beneficios.push(b);

	}

	cout << mayorBeneficio(beneficios, L) << '\n';

	return true;

}

int main() {

	while (testCase());

	return 0;

}
