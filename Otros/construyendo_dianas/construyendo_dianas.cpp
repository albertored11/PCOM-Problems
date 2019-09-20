#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_SECTORES = 50;
const int MAX_VALOR = 500;
const int INFINITO = 1000;

int calcularLaMatris(int sector, int valor, vector<int> sectores, int numTiradas[MAX_SECTORES + 1][MAX_VALOR + 1]) {

	int nTiradas = numTiradas[sector][valor];

	if (nTiradas != -1)
		return nTiradas;

	if (valor == 0)
		return numTiradas[sector][valor] = 0;

	if (sector == 0)
		return numTiradas[sector][valor] = INFINITO;

	if (valor < sectores[sector - 1])
		return numTiradas[sector][valor] = calcularLaMatris(sector - 1, valor, sectores, numTiradas);
	else
		return numTiradas[sector][valor] = min(calcularLaMatris(sector, valor - sectores[sector - 1], sectores, numTiradas) + 1,
				   calcularLaMatris(sector - 1, valor, sectores, numTiradas));

}

void printSolucion(int valor, vector<int> sectores, const int numTiradas[MAX_SECTORES + 1][MAX_VALOR + 1]) {

	/*for (int i = 0; i < sectores.size() + 1; ++i) {
		for (int j = 0; j < valor + 1; ++j)
			cout << numTiradas[i][j] << ' ';
		cout << '\n';
	}*/

	int sector = sectores.size();
	int nTiradas = numTiradas[sector][valor];

	if (nTiradas > valor)
		cout << "Imposible";
	else {
		cout << nTiradas << ':';

		while (valor > 0) {

			if (valor >= sectores[sector - 1] && numTiradas[sector][valor - sectores[sector - 1]] == nTiradas - 1) {
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
	int numTiradas[MAX_SECTORES + 1][MAX_VALOR + 1];
	vector<int> sectores;
	vector<int> actual;
	vector<int> mejor;

	cin >> numSectores;

	for (int i = 0; i < numSectores; ++i) {
		int sector;
		cin >> sector;
		sectores.push_back(sector);
	}

	for (int i = 0; i <= numSectores; ++i)
		for (int j = 0; j <= valor; ++j)
			numTiradas[i][j] = -1;

	calcularLaMatris(numSectores, valor, sectores, numTiradas);
	printSolucion(valor, sectores, numTiradas);

	return true;

}

int main() {

	while (resuelve());

	return 0;

}
