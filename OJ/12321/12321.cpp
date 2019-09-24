#include <iostream>
#include <set>

using namespace std;

int caso = 1;

typedef struct {
	int ini;
	int fin;
} tIntervalo;

bool operator<(tIntervalo a, tIntervalo b) {

	if (a.fin == b.fin)
		return a.ini > b.ini;

	return a.fin > b.fin;

}

bool operator==(tIntervalo a, tIntervalo b) {

	return a.ini == b.ini && a.fin == b.fin;

}

bool operator>(tIntervalo a, tIntervalo b) {

	if (a.fin == b.fin)
		return a.ini < b.ini;

	return a.fin < b.fin;

}

bool resuelve() {

	int L, G;

	cin >> L >> G;

	if (L == 0 && G == 0)
		return false;

	set<tIntervalo> intervalos;

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
			inter.fin = L;
*/

		intervalos.insert(inter);

	}

	int pos = 0;
	int numGasCerradas = G;

	while (pos <= L) {

		set<tIntervalo>::iterator iter = intervalos.begin();

		while (!(iter->ini <= pos && iter->fin >= pos) && iter != intervalos.end())
			++iter;

		if (iter == intervalos.end())
			break;

		intervalos.erase(iter);

		pos = iter->fin;

		--numGasCerradas;

	}

	if (pos <= L)
		numGasCerradas = -1;

	cout << numGasCerradas << '\n';

	return true;

}

int main() {

	while (resuelve()) ++caso;

	return 0;

}
