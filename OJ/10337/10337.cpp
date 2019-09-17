#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

const int MAX_ALTITUD = 10;
const int MAX_DIST = 1000;

int distancia;
int viento[MAX_ALTITUD][MAX_DIST];
int gasolinaMinGastada[MAX_ALTITUD][MAX_DIST]; // filas = altitud, columnas = posición

int gasolinaMinima(int posicion, int altitud) {

	if (posicion == distancia)
		return viento[9][distancia - 1];

	int subida = INT_MAX;
	int mant = INT_MAX;
	int bajada = INT_MAX;

	if (gasolinaMinGastada[posicion][9 - altitud] != -1)
		return gasolinaMinGastada[posicion][9 - altitud];

	if (altitud < 9 && distancia - posicion - 1 > altitud) {

		subida = 60
				- viento[posicion][9 - altitud]
				+ gasolinaMinima(posicion + 1, altitud + 1);

	}

	if (altitud > 0) {

		bajada = 20
				- viento[posicion][9 - altitud]
				+ gasolinaMinima(posicion + 1, altitud - 1);
	}

	if (distancia - posicion > altitud) {

		mant = 30
			 - viento[posicion][9 - altitud]
			 + gasolinaMinima(posicion + 1, altitud);

	}

	return gasolinaMinGastada[posicion][9 - altitud] = min(subida, min(bajada, mant));

}

void resuelve() {

	int posicion = 0;
	int altitud = 0;

	cin >> distancia;

	distancia /= 100;

	for (int i = 0; i < MAX_ALTITUD; ++i)
		for (int j = 0; j < distancia; ++j)
			cin >> viento[i][j];

	memset(gasolinaMinGastada, -1, MAX_ALTITUD * MAX_DIST * sizeof(int));

	cout << gasolinaMinima(posicion, altitud) << "\n\n";

}

int main() {

	int nCasos;

	cin >> nCasos;

	while(nCasos--)
		resuelve();

	return 0;

}
