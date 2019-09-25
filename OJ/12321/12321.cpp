#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int caso = 1;

typedef struct {
	int ini;
	int fin;
} tIntervalo;

bool operator<(tIntervalo a, tIntervalo b) {

	if (a.ini == b.ini)
		return a.fin < b.fin;

	return a.ini < b.ini;

}

bool operator==(tIntervalo a, tIntervalo b) {

	return a.ini == b.ini && a.fin == b.fin;

}

bool operator>(tIntervalo a, tIntervalo b) {

	if (a.ini == b.ini)
		return a.fin > b.fin;

	return a.ini > b.ini;

}

bool resuelve() {

	int L, G;

	cin >> L >> G;

	if (L == 0 && G == 0)
		return false;

	vector<tIntervalo> intervalos;

	for (int i = 0; i < G; ++i) {

		tIntervalo inter;
		int x, r;

		cin >> x >> r;

		inter.ini = x - r;
/*

		if (inter.ini < 0)
			inter.ini = 0;
*/

		inter.fin = x + r;
/*
		if (inter.fin > L)
			inter.fin = L;*/

		intervalos.push_back(inter);

	}

	sort(intervalos.begin(), intervalos.end());

	int pos = 0;
	int numGasCerradas = G;
	int mayorFin;
	int i = 0;

	while (pos < L && i < intervalos.size()) {

		mayorFin = -1;

		while (intervalos[i].ini <= pos && i < intervalos.size()) {
			mayorFin = max(mayorFin, intervalos[i].fin);
			++i;
		}

		if (mayorFin == -1)
			break;

		pos = mayorFin;

		--numGasCerradas;

	}

	if (mayorFin == -1 || pos < L)
		numGasCerradas = -1;

	cout << numGasCerradas << '\n';

	return true;

}

int main() {

	while (resuelve()) ++caso;

	return 0;

}
