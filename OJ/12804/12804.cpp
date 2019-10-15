#include <iostream>
#include <vector>

using namespace std;

typedef enum {
	VIRGEN, TOCADO, HUNDIDO
} tEstado;

using vi = vector<int>;
using vvi = vector<vi>;
using vestado = vector<tEstado>;

vestado estado;
vvi adjList;
int numCaso = 1;

void dfs(int u, int lines, bool &hayCiclo, bool &termina) {

	if (hayCiclo && termina)
		return;

	estado[u] = TOCADO;

	for (int i = 0; i < adjList[u].size(); ++i) {

		if (hayCiclo && termina)
			return;

		int v = adjList[u][i];

		if (v > lines)
			termina = true;
		else if (estado[v] == TOCADO)
			hayCiclo = true;
		else
			dfs(v, lines, hayCiclo, termina);

		if (hayCiclo && termina)
			return;

	}

	estado[u] = HUNDIDO;

}

void resuelve() {

	int lines;
	bool termina = false;
	char ins;

	cin >> lines;

	estado.assign(lines + 1, VIRGEN);

	adjList.assign(lines + 1, vi());

	for (int i = 1; i <= lines; ++i) {

		cin >> ins;

		if (ins == 'A' || ins == 'C')
			adjList[i].push_back(i + 1);

		if (ins == 'J' || ins == 'C') {

			int next;

			cin >> next;

			adjList[i].push_back(next);

		}

	}
/*
	if (ins == 'A')
		termina = true;*/

	bool hayCiclo = false;
	dfs(1, lines, hayCiclo, termina);

	if (!termina)
		cout << "NEVER\n";
	else if (hayCiclo)
		cout << "SOMETIMES\n";
	else
		cout << "ALWAYS\n";


}

int main() {

	int nCasos;

	cin >> nCasos;

	while (nCasos--) {
		resuelve();
		++numCaso;
	}

	return 0;

}
