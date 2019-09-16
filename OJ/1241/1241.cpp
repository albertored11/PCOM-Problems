#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

bool participa(bool participantes[1100], int ini, int fin, int &numWO) {

	if (ini == fin)
		return participantes[ini];
	
	bool par1 = participa(participantes, ini, (ini + fin) / 2, numWO);
	bool par2 = participa(participantes, (ini + fin) / 2 + 1, fin, numWO);

	if (par1 && par2)
		return true;

	if (par1 || par2) {
		++numWO;
		return true;
	}

	return false;

}

void resuelve() {

	int n, m, numWO = 0;
	bool participantes[1100];

	memset(participantes, 1, sizeof(bool) * 1100);

	cin >> n >> m;

	for (int i = 0; i < m; ++i) {
		int p;
		cin >> p;
		participantes[p - 1] = false;
	}

	participa(participantes, 0, pow(2, n) - 1, numWO);

	cout << numWO << '\n';

}

int main() {

	int nCasos;

	cin >> nCasos;

	while (nCasos--)
		resuelve();

	return 0;

}
