#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using ii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;

int empleados;
vvi adjList;

void resuelve() {

	int fuente;

	cin >> fuente;

	vb visitados;
	int numEmpleadosDia = 0;
	int dia = 0;
	int maxEmpleados = 0;
	int diaMaxEmpleados = 0;
	queue<ii> q;

	visitados.assign(empleados, false);
	visitados[fuente] = true;
	q.push({0, fuente});

	while (!q.empty()) {

		ii v = q.front();
		q.pop();

		if (dia == v.first) {
			if (dia != 0)
				++numEmpleadosDia;
		}
		else {

			if (numEmpleadosDia > maxEmpleados) {
				maxEmpleados = numEmpleadosDia;
				diaMaxEmpleados = dia;
			}

			numEmpleadosDia = 1;
			++dia;

		}

		for (int w : adjList[v.second]) {
			if (!visitados[w]) {
				visitados[w] = true;
				q.push({v.first + 1, w});
			}
		}

	}

	if (numEmpleadosDia > maxEmpleados) {
		maxEmpleados = numEmpleadosDia;
		diaMaxEmpleados = dia;
	}

	if (maxEmpleados == 0)
		cout << 0 << '\n';
	else
		cout << maxEmpleados << ' ' << diaMaxEmpleados << '\n';

}

int main() {

	cin >> empleados;

	adjList.resize(empleados);

	for (int i = 0; i < empleados; ++i) {

		int amigos;

		cin >> amigos;

		for (int j = 0; j < amigos; ++j) {

			int compa;

			cin >> compa;

			adjList[i].push_back(compa);
//			adjList[compa].push_back(i);

		}

	}

	int nCasos;

	cin >> nCasos;

	while (nCasos--) resuelve();

	return 0;

}
