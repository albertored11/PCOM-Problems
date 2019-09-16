#include <iostream>

using namespace std;

bool testCase() {

	int L;

	cin >> L;

	if (L == 0)
		return false;

	int maximoBeneficio = 0;
	int beneficioActual = 0;
	int prefijo = 0;
	int mejorPrefijo = 0;
	int sufijo = 0;

	for (int i = 0; i < L; ++i) {

		int benef;

		cin >> benef;

		beneficioActual += benef;

		if (beneficioActual < 0)
			beneficioActual = 0;
		else if (beneficioActual > maximoBeneficio)
			maximoBeneficio = beneficioActual;

		prefijo += benef;

		if (prefijo > mejorPrefijo) {
			mejorPrefijo = prefijo;
			sufijo = 0;
		}

		if (mejorPrefijo > 0) {

			sufijo += benef;

			if (sufijo < 0)
				sufijo = 0;

		}

	}

	if (mejorPrefijo + sufijo > maximoBeneficio)
		cout << mejorPrefijo + sufijo;
	else
		cout << maximoBeneficio;

	cout << '\n';

	return true;

}

int main() {

	while (testCase());

	return 0;

}
