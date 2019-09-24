#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cstring>
#include <queue>

using namespace std;

void dfs(int origen, int destino, vector<int> &recorrido, vector<int> &mejorRecorrido, vector<bool> &visited, vector<vector<int>> adjListList) {

	for (int w : adjListList[origen]) {

		if (w == destino) {

			recorrido.push_back(w);

			if (recorrido.size() < mejorRecorrido.size() || mejorRecorrido.size() == 0)
				mejorRecorrido = recorrido;

			recorrido.pop_back();

			break;

		}

		if (!visited[w]) {
			visited[w] = true;
			recorrido.push_back(w);
			dfs(w, destino, recorrido, mejorRecorrido, visited, adjListList);
			recorrido.pop_back();
			visited[w] = false;
		}

	}

}

bool resuelve() {

	int edges;

	cin >> edges;

	if (!cin)
		return false;

	vector<vector<int>> adjListList;
	vector<string> cities;
	unordered_map<string, int> cityCode;
	vector<bool> visited;
	string origen, destino;
	vector<int> recorrido;
	vector<int> mejorRecorrido;

	for (int i = 0; i < edges; ++i) {

		string city0, city1;

		cin >> city0 >> city1;

		if (cityCode.count(city0) == 0) {
			cityCode.emplace(city0, cities.size());
			cities.push_back(city0);
		}

		if (cityCode.count(city1) == 0) {
			cityCode.emplace(city1, cities.size());
			cities.push_back(city1);
		}

		adjListList[cityCode.at(city0)].push_back(cityCode.at(city1));
		adjListList[cityCode.at(city1)].push_back(cityCode.at(city0));

	}

	cin >> origen >> destino;

	memset(&visited, 0, cities.size() * sizeof(bool));

	dfs(cityCode.at(origen), cityCode.at(destino), recorrido, mejorRecorrido, visited, adjListList);

	if (mejorRecorrido.size() == 0)
		cout << "No route\n";
	else {

		cout << cities[mejorRecorrido[0]];

		for (int i = 1; i < mejorRecorrido.size() - 1; ++i)
			cout << ' ' << cities[mejorRecorrido[i]] << '\n' << cities[mejorRecorrido[i]];

		cout << cities[mejorRecorrido[mejorRecorrido.size() - 1]];

	}

	return true;

}

int main() {

	while (resuelve());

	return 0;

}
