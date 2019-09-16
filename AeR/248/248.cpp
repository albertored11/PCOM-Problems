// Segunda versión. Da WA, pero no encuentro un caso que falle.

#include <iostream>

using namespace std;

bool testCase() {

	int L;

	cin >> L;

	if (L == 0)
		return false;

	int maximoBeneficio = 0;
	int prefijo = 0;
	int sufijo = 0;
	int beneficioActual = 0;
	bool empiezaSufijo = false;

	for (int i = 0; i < L; ++i) {

		int benef;

		cin >> benef;

		beneficioActual += benef;

		if (beneficioActual < 0)
			beneficioActual = 0;
		else if (beneficioActual > maximoBeneficio)
			maximoBeneficio = beneficioActual;

		if (prefijo <= 0)
			prefijo += benef;
		else if (!empiezaSufijo && benef >= 0) {
			empiezaSufijo = true;
			sufijo += benef;
		}
		else if (empiezaSufijo)
			sufijo += benef;

	}

	if (prefijo + sufijo > maximoBeneficio)
		cout << prefijo + sufijo;
	else
		cout << maximoBeneficio;

	cout << '\n';

	return true;

}

int main() {

	while (testCase());

	return 0;

}
