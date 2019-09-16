#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <unordered_set>
using namespace std;

typedef struct {
	int valores[2];
	bool usado;
} tPieza;

bool domino(tPieza piezaFin, vector<tPieza> piezas, int num, int numUsados, int n) {

	bool ret = false;

	if (numUsados == n) {

		if (piezaFin.valores[0] == num /*|| piezaFin.valores[1] == num*/)
			return true;

	}
	else {

		int i = 0;

		while (i < piezas.size() && !ret) {

			if (piezas[i].valores[0] == num && !piezas[i].usado) {
				piezas[i].usado = true;
				ret = domino(piezaFin, piezas, piezas[i].valores[1], numUsados + 1, n);
				piezas[i].usado = false;
			}
			else if (piezas[i].valores[1] == num && !piezas[i].usado) {
				piezas[i].usado = true;
				ret = domino(piezaFin, piezas, piezas[i].valores[0], numUsados + 1, n);
				piezas[i].usado = false;
			}

			++i;

		}

	}

	return ret;

}

bool domino(tPieza piezaIni, tPieza piezaFin, vector<tPieza> piezas, int n) {

	return //domino(piezaFin, piezas, piezaIni.valores[0], 0, n) ||
			domino(piezaFin, piezas, piezaIni.valores[1], 0, n);

}

bool resuelve() {

	int n;

	cin >> n;

	if (n == 0)
		return false;

	int m;
	tPieza pieza;
	tPieza piezaIni;
	tPieza piezaFin;
	vector<tPieza> piezas;

	cin >> m;

	cin >> piezaIni.valores[0] >> piezaIni.valores[1];
	cin >> piezaFin.valores[0] >> piezaFin.valores[1];

	for (int i = 0; i < m; ++i) {
		cin >> pieza.valores[0] >> pieza.valores[1];
		pieza.usado = false;
		piezas.push_back(pieza);
	}

	if (domino(piezaIni, piezaFin, piezas, n))
		cout << "YES\n";
	else
		cout << "NO\n";

	return true;

}

int main() {

	while (resuelve());

	return 0;

}
