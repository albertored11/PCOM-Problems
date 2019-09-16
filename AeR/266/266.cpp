#include <iostream>

using namespace std;

const int MAX_TAM = 500;

bool testCase() {

	int filas, columnas;

	cin >> filas >> columnas;

	if (filas == 0 && columnas == 0)
		return false;

	char cuadro[MAX_TAM][MAX_TAM];
	int numDalt;
	char letras[50];

	for (int i = 0; i <= 'Z' - 'A'; ++i)
		letras[i] = 'A' + i;

	for (int i = 0; i < filas; ++i)
		for (int j = 0; j < columnas; ++j)
			cin >> cuadro[i][j];

	cin >> numDalt;

	for (int i = 0; i < numDalt; ++i) {

		char color1, color2;

		cin >> color1 >> color2;

		for (int j = 0; j <= 'Z' - 'A'; ++j)
			if (letras[j] == color1)
				letras[j] = color2;

	}

	for (int i = 0; i < filas; ++i) {

		for (int j = 0; j < columnas; ++j)
			cout << letras[cuadro[i][j] - 'A'];

		cout << '\n';

	}

	return true;

}

int main() {

	while (testCase());

	return 0;

}
