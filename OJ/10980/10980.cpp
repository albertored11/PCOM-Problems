#include <iostream>
#include <set>
#include <vector>
#include <string>


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

typedef struct {
	int units;
	double unitPrice;
} tPack;

bool operator<(tPack a, tPack b) {

	return a.unitPrice < b.unitPrice;

}

bool operator==(tPack a, tPack b) {

	return a.unitPrice == b.unitPrice;

}

bool operator>(tPack a, tPack b) {

	return a.unitPrice > b.unitPrice;

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

void createMatrix(int units, set<tPack> packs)

void bestDeal(int units, set<tPack> packs) {

	double price;

	while(units > 0) {
		set<tPack>::const_iterator best = packs.begin();
		if(best)


	}


}

bool resuelve() {

	double unitPrice;

	cin >> unitPrice;

	if (!cin)
		return false;

	int m;
	set<tPack> packs;
	string line;
	vector<int> testCases;

	cin >> m;

	tPack p;

	p.units = 1;
	p.unitPrice = unitPrice;
	packs.emplace(p);

	for (int i = 0; i < m; ++i) {

		tPack p;

		cin >> p.units >> p.unitPrice;
		p.unitPrice /= p.units;
		packs.emplace(p);

	}

	getline(cin, line);
	testCases = parseLine(line);

	for (int i = 0; i < testCases.size(); ++i) {
		cout << "Case " << i + 1 << ":\n";
		bestDeal(testCases[i], packs);
	}
	return true;

}

int main() {

	while (resuelve());

	return 0;

}
