#include <iostream>
#include <vector>

using namespace std;

const int MAX_SECTORES = 50;

void mejorTirada(int valor, int numSectores, int sectorActual, int sectores[], vector<int> actual, vector<int> &mejor) {

	if (valor == 0) {

		if (actual.size() < mejor.size() || mejor.size() == 0)
			mejor = actual;
		else if (actual.size() == mejor.size()) {

			int i = 0;

			while (i < actual.size() && actual[i] == mejor[i])
				++i;

			if (i != actual.size() && actual[i] > mejor[i])
				mejor = actual;

		}

	}
	else {

		for (int i = sectorActual; i < numSectores; ++i) {
			int tirada = sectores[i];
			if(tirada <= valor) {
				actual.push_back(tirada);
				mejorTirada(valor - tirada, numSectores, i, sectores, actual, mejor);
				actual.pop_back();
			}
		}

	}

}

bool resuelve() {

	int valor;

	cin >> valor;

	if (!cin)
		return false;

	int numSectores;
	int sectores[MAX_SECTORES];
	vector<int> actual;
	vector<int> mejor;

	cin >> numSectores;

	for (int i = 0; i < numSectores; ++i)
		cin >> sectores[numSectores - i - 1];

	mejorTirada(valor, numSectores, 0, sectores, actual, mejor);

	if (mejor.size() == 0)
		cout << "Imposible\n";
	else {

		cout << mejor.size() << ':';

		for (int i = 0; i < mejor.size(); ++i)
			cout << ' ' << mejor[i];

		cout << '\n';

	}

	return true;

}

int main() {

	while (resuelve());

	return 0;

}
