#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <unordered_set>

using namespace std;

void resuelve(int index) {

	vector<unordered_set<int>> chocosExclusivos;
	vector<unordered_set<int>> chocosFaltantes;
	unordered_set<int> chocosFaltantes3Borrados;

	for (int i = 0; i < 3; ++i) {
		unordered_set<int> chocos;
		chocosExclusivos.push_back(chocos);
	}

	for (int i = 0; i < 3; ++i) {
		unordered_set<int> chocos;
		chocosFaltantes.push_back(chocos);
	}

	int l, r, s;

	cin >> l >> r >> s;

	for (int i = 0; i < l; ++i) {

		int choco;

		cin >> choco;

		chocosExclusivos[0].insert(choco);

	}

	for (int i = 0; i < r; ++i) {

		int choco;

		cin >> choco;

		if (chocosExclusivos[0].count(choco) == 1) {
			chocosExclusivos[0].erase(choco);
			chocosFaltantes[2].insert(choco);
		}
		else if (chocosFaltantes[2].count(choco) == 0)
			chocosExclusivos[1].insert(choco);

	}

	for (int i = 0; i < s; ++i) {

		int choco;

		cin >> choco;

		if (chocosExclusivos[0].count(choco) == 1) {
			chocosExclusivos[0].erase(choco);
			chocosFaltantes[1].insert(choco);
		}
		else if (chocosExclusivos[1].count(choco) == 1) {
			chocosExclusivos[1].erase(choco);
			chocosFaltantes[0].insert(choco);
		}
		else if (chocosFaltantes[2].count(choco) == 1) {
			chocosFaltantes[2].erase(choco);
			chocosFaltantes3Borrados.insert(choco);
		}
		else if (chocosFaltantes[1].count(choco) == 0 && chocosFaltantes[0].count(choco) == 0 && chocosFaltantes3Borrados.count(choco) == 0)
			chocosExclusivos[2].insert(choco);

	}

	cout << "Case #" << index + 1 << ":\n";

	for (int i = 0; i < 3; ++i)
		cout << chocosExclusivos[i].size() << ' ' << chocosFaltantes[i].size() << '\n';

}

int main() {

	int nCasos;

	cin >> nCasos;

	for (int i = 0; i < nCasos; ++i)
		resuelve(i);

	return 0;

}
