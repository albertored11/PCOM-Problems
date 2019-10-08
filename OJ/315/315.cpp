#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <unordered_set>

using namespace std;

using vi = vector<int>;
using vii = vector<vi>;

const int MAX = 100;

int hora;
int horaVertice[MAX];
int alcanzable[MAX];
int hijosRaiz;

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

void dfs(int u, int uParent, vii adjList, unordered_set<int> &criticalPlaces) {

	horaVertice[u] = alcanzable[u] = hora;
	++hora;

	for (int i = 0; i < adjList[u].size(); ++i) {

		int v = adjList[u][i];

		if (v == uParent)
			continue;

		if (horaVertice[v] == 0) {

			if (uParent == 0)
				++hijosRaiz;

			dfs(v, u, adjList, criticalPlaces);

			if (alcanzable[v] >= horaVertice[u]) {

				if (uParent != 0)
					criticalPlaces.emplace(u);

				alcanzable[u] = min(alcanzable[u], alcanzable[v]);

			}
			else
				alcanzable[u] = min(alcanzable[u], horaVertice[v]);

		}

	}

}

bool resuelve() {

	int N;

	cin >> N;

	if (N == 0)
		return false;

	string lineStr;
	vi line;
	vii adjList(N + 1);
	unordered_set<int> criticalPlaces;

	cin.ignore();
	getline(cin, lineStr);
	line = parseLine(lineStr);

	while (line[0] > 0) {

		for (int i = 1; i < line.size(); ++i) {
			adjList[line[0]].push_back(line[i]);
			adjList[line[i]].push_back(line[0]);
		}

//		cin.ignore();
		getline(cin, lineStr);
		line = parseLine(lineStr);

	}

	hora = 1;
	hijosRaiz = 0;
	memset(horaVertice, 0, MAX * sizeof(horaVertice[0]));
	memset(alcanzable, -1, MAX * sizeof(alcanzable[0]));

	for (int i = 1; i <= N; ++i) {

		if (!horaVertice[i]) {

			hijosRaiz = 0;
			dfs(i, 0, adjList, criticalPlaces);

			if (hijosRaiz > 1)
				criticalPlaces.emplace(i);

		}

	}

	cout << criticalPlaces.size() << '\n';

	return true;

}

int main() {

	while (resuelve());

	return 0;

}
