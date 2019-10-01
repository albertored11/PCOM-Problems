#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using ii = pair<int, int>;
using vi = vector<int>;
using vii = vector<ii>;

const int INF = 100000;

bool resuelve() {

	int celdas;

	cin >> celdas;

	if (!cin)
		return false;

	int salida, tiempo, pasadizos;
	vector<vii> adjList;
	vi distancias;
	int count = 0;

	adjList.resize(celdas + 1);

	cin >> salida >> tiempo >> pasadizos;

	for (int i = 0; i < pasadizos; ++i) {

		int a;
		pair<int, int> p;

		cin >> p.second >> a >> p.first;

		adjList[a].push_back(p);

	}

	priority_queue<ii, vii, greater<ii>> pq;

	distancias.assign(celdas + 1, INF);

	distancias[salida] = 0;
	pq.push({0, salida});

	while (!pq.empty()) {

		ii front = pq.top();
		pq.pop();

		int d = front.first, u = front.second;

		if (d > distancias[u]) continue;

		for (auto a : adjList[u]) {

			if (distancias[u] + a.first < distancias[a.second]) {
				distancias[a.second] = distancias[u] + a.first;
				pq.push({distancias[a.second], a.second});
			}

		}

	}

	for (int i = 1; i <= celdas; ++i)
		if (distancias[i] <= tiempo)
			++count;

	cout << count - 1 << '\n';

	return true;

}

int main() {

	while (resuelve());

	return 0;

}
