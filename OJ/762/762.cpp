#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

bool first = true;

bool bfs(vector<vector<int>> adjList, int origen, int destino, int numCities, vector<int> &pred) {

	queue<int> q;
	vector<bool> visited;

	for (int i = 0; i < numCities; ++i) {
		visited.push_back(false);
		pred.push_back(-1);
	}

	visited[origen] = true;
	q.push(origen);

	while (!q.empty()) {

		int city = q.front();
		q.pop();

		for (int city1 : adjList[city]) {

			if (!visited[city1]) {

				visited[city1] = true;
				pred[city1] = city;
				q.push(city1);

				if (city1 == destino)
					return true;

			}

		}

	}

	return false;

}

bool resuelve() {

	int edges;

	cin >> edges;

	if (!cin)
		return false;

	vector<vector<int>> adjList;
	vector<string> cities;
	unordered_map<string, int> cityCode;
	vector<int> pred;
	string origen, destino;

	for (int i = 0; i < edges + 1; ++i) {

		string city0, city1;

		cin >> city0 >> city1;

		if (cityCode.count(city0) == 0) {
			vector<int> v;
			cityCode.emplace(city0, cities.size());
			cities.push_back(city0);
			adjList.push_back(v);
		}

		if (cityCode.count(city1) == 0) {
			vector<int> v;
			cityCode.emplace(city1, cities.size());
			cities.push_back(city1);
			adjList.push_back(v);
		}

		if (i < edges) {
			adjList[cityCode.at(city0)].push_back(cityCode.at(city1));
			adjList[cityCode.at(city1)].push_back(cityCode.at(city0));
		}
		else {
			origen = city0;
			destino = city1;
		}

	}


	if (!first)
		cout << '\n';
	else
		first = false;

	if (!bfs(adjList, cityCode.at(origen), cityCode.at(destino), cities.size(), pred)) {
		cout << "No route\n";
	}
	else {

		stack<int> s;

		s.push(cityCode.at(destino));

		while (pred[s.top()] != -1)
			s.push(pred[s.top()]);

		cout << cities[s.top()];
		s.pop();

		while (s.size() > 1) {
			cout << ' ' << cities[s.top()] << '\n' << cities[s.top()];
			s.pop();
		}

		cout << ' ' << cities[s.top()];
		s.pop();

		cout << '\n';

	}

	return true;

}

int main() {

	while (resuelve());

	return 0;

}
