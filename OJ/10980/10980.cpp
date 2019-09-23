#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <cfloat>
#include <iomanip>


/*

HOLA AMIGOS DEL FUTURO

 LA MATRIZ GUARDA EN CADA CASILLA EL MEJOR PRECIO PARA COMPRAR J UNIDADES
 CONSIDERANDO LOS PACKS (0..i) ORDENADOS DE MAYOR A MENOR PRECIO UNITARIO
 IGUAL QUE LAS DIANAS
 PENSAR COMO GUARDAR LAS OFERTAS
 GOOD LUCK CRACKS
 EL QUE HA ESCRITO ESTO ES UN GENIO

*/

using namespace std;

const double INFINITO = 3000;//DBL_MAX;

typedef struct {
	int units;
	double unitPrice;
} tPack;

bool operator<(tPack a, tPack b) {

	return a.unitPrice > b.unitPrice;

}

bool operator==(tPack a, tPack b) {

	return a.unitPrice == b.unitPrice;

}

bool operator>(tPack a, tPack b) {

	return a.unitPrice < b.unitPrice;

}

vector<int> parseLine(string line) {

	vector<int> ret;
	string aux;
	int i = 0;

	while (i < line.length()) {

		aux = "";

		while (i < line.length() && line[i] != ' ') {
			aux += line[i];
			++i;
		}

		if (aux != "")
			ret.push_back(stoi(aux));

		++i;

	}

	return ret;

}

void printMatrix(const vector<vector<double>> mat) {

	for (int i = 0; i < mat.size(); ++i) {
		for (int j = 0; j < mat[i].size(); ++j)
			cout << mat[i][j] << ' ';

		cout << '\n';
	}

	cout << '\n';

}

double createMatrix(int pack, int units, vector<tPack> packs, vector<vector<double>> &mejoresPrecios) {

	double mejorPrecio = mejoresPrecios[pack][units];

	printMatrix(mejoresPrecios);

	if (mejorPrecio != -1)
		return mejorPrecio;

	if (units <= 0)
		return mejoresPrecios[pack][0] = 0;

	if (pack == 0)
		return mejoresPrecios[pack][units] = INFINITO;

	double totalPrice = packs[pack - 1].unitPrice * packs[pack - 1].units;

	return mejoresPrecios[pack][units] = min(createMatrix(pack, units - packs[pack - 1].units, packs, mejoresPrecios) + totalPrice,
			createMatrix(pack - 1, units, packs, mejoresPrecios));

}

bool resuelve(int numCase) {

	double unitPrice;

	cin >> unitPrice;

	if (!cin)
		return false;

	int m;
	set<tPack> packSet;
	string line;
	vector<int> testCases;
	vector<tPack> packs;

	cin >> m;

	tPack p;

	p.units = 1;
	p.unitPrice = unitPrice;
	packSet.emplace(p);

	for (int i = 0; i < m; ++i) {

		tPack p;

		cin >> p.units >> p.unitPrice;
		p.unitPrice /= p.units;
		packSet.emplace(p);

	}

	set<tPack>::const_iterator iter = packSet.cbegin();

	while (iter != packSet.cend()) {

		packs.push_back(*iter);

		++iter;

	}

	string dummy;

	getline(cin, dummy);
	getline(cin, line);
	testCases = parseLine(line);

	cout << "Case " << numCase << ":\n";

	for (int i = 0; i < testCases.size(); ++i) {

		vector<vector<double>> mejoresPrecios;

		mejoresPrecios.resize(m + 2);

		for (int j = 0; j < m + 2; ++j)
			mejoresPrecios[j].resize(testCases[i] + 1, -1);

		createMatrix(m + 1, testCases[i], packs, mejoresPrecios);

		cout << "Buy " << testCases[i] << " for $" << fixed << setprecision(2) << mejoresPrecios[m + 1][testCases[i]] << '\n';

	}

	return true;

}

int main() {

	int i = 1;

	while (resuelve(i)) ++i;

	return 0;

}
