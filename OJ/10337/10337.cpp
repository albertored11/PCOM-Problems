#include <iostream>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

const int MAX_ALTITUD = 10;
const int MAX_DIST = 1000;



int gasolinaMinima(int posicion, int altitud, int distancia, int viento[MAX_ALTITUD][MAX_DIST], int gasolinaMinGastada[MAX_ALTITUD][MAX_DIST]) {

	if (posicion == distancia)
		return viento[9][distancia - 1];

	int subida = INT_MAX;
	int mant = INT_MAX;
	int bajada = INT_MAX;

	if (posicion != 0 && gasolinaMinGastada[9 - altitud][posicion - 1] != -1)
		return gasolinaMinGastada[9 - altitud][posicion - 1];

	int vientoActual = 0;

	if (posicion != 0)
		vientoActual = viento[9 - altitud][posicion - 1];

	if (altitud < 9 && distancia - posicion - 1 > altitud) {

		subida = 60
				- vientoActual
				+ gasolinaMinima(posicion + 1, altitud + 1, distancia, viento, gasolinaMinGastada);

	}

	if (altitud > 0) {

		bajada = 20
				- vientoActual
				+ gasolinaMinima(posicion + 1, altitud - 1, distancia, viento, gasolinaMinGastada);
	}

	if (distancia - posicion > altitud) {

		mant = 30
			 - vientoActual
			 + gasolinaMinima(posicion + 1, altitud, distancia, viento, gasolinaMinGastada);

	}

	return gasolinaMinGastada[9 - altitud][posicion - 1] = min(subida, min(bajada, mant));

}

void resuelve() {

	int distancia;
	int viento[MAX_ALTITUD][MAX_DIST];
	int gasolinaMinGastada[MAX_ALTITUD][MAX_DIST]; // filas = altitud, columnas = posición

	int posicion = 0;
	int altitud = 0;

	cin >> distancia;

	distancia /= 100;

	for (int i = 0; i < MAX_ALTITUD; ++i)
		for (int j = 0; j < distancia; ++j)
			cin >> viento[i][j];

	memset(gasolinaMinGastada, -1, MAX_ALTITUD * MAX_DIST * sizeof(int));

	cout << gasolinaMinima(posicion, altitud, distancia, viento, gasolinaMinGastada) << "\n\n";

}

int main() {

	int nCasos;

	cin >> nCasos;

	while(nCasos--)
		resuelve();

	return 0;

}
