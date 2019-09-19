#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_SECTORES = 50;
const int MAX_VALOR = 500;
const int INFINITO = 1000;

int calcularLaMatris(int sector, int valor, vector<int> sectores, int numTiradas[MAX_SECTORES][MAX_VALOR]) {

	if (valor == 0)
		return numTiradas[sector - 1][valor] = 0;

	if (sector != 0) {

		if (valor < sectores[sector - 1])
			return numTiradas[sector - 1][valor] = calcularLaMatris(sector - 1, valor, sectores, numTiradas);
		else
			return numTiradas[sector - 1][valor] = min(calcularLaMatris(sector, valor - sectores[sector - 1], sectores, numTiradas) + 1,
					   calcularLaMatris(sector - 1, valor, sectores, numTiradas));

	}

	return numTiradas[sector][valor] = INFINITO;

}

void printSolucion(int valor, vector<int> sectores, const int numTiradas[MAX_SECTORES][MAX_VALOR]) {

	/*for (int i = 0; i < sectores.size(); ++i) {
		for (int j = 0; j < valor + 1; ++j)
			cout << numTiradas[i][j] << ' ';
		cout << '\n';
	}*/

	int sector = sectores.size();
	int nTiradas = numTiradas[sector - 1][valor];

	if (nTiradas > valor)
		cout << "Imposible";
	else {
		cout << nTiradas << ':';

		while (valor > 0) {

			if (valor >= sectores[sector - 1] && numTiradas[sector - 1][valor - sectores[sector - 1]] == nTiradas - 1) {
				cout << ' ' << sectores[sector - 1];
				valor -= sectores[sector - 1];
				--nTiradas;
			}
			else {
				--sector;
			}

		}

	}

	cout << '\n';

}

bool resuelve() {

	int valor;

	cin >> valor;

	if (!cin)
		return false;

	int numSectores;
	int numTiradas[MAX_SECTORES][MAX_VALOR];
	vector<int> sectores;
	vector<int> actual;
	vector<int> mejor;

	cin >> numSectores;

	for (int i = 0; i < numSectores; ++i) {
		int sector;
		cin >> sector;
		sectores.push_back(sector);
	}

	calcularLaMatris(numSectores, valor, sectores, numTiradas);
	printSolucion(valor, sectores, numTiradas);

	return true;

}

int main() {

	while (resuelve());

	return 0;

}
