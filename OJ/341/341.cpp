#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
using vvii = vector<vii>;

int numCasos = 1;

const int INF = 10e7;

bool resuelve() {

	int N;

	cin >> N;

	if (N == 0)
		return false;

	vvii adjList(N + 1);
	int ini, fin;
	priority_queue<ii, vii, greater<ii>> pq;
	vi dist;
	vi pred;

	for (int i = 1; i <= N; ++i) {

		int numAdj;

		cin >> numAdj;

		for (int j = 0; j < numAdj; ++j) {

			ii elem;

			cin >> elem.second >> elem.first;

			adjList[i].push_back(elem);

		}

	}

	cin >> ini >> fin;

	dist.assign(N + 1, INF);
	pred.resize(N + 1);
	dist[ini] = 0;
	pq.push({0, ini});

	while (pq.top().second != fin) {

		ii front = pq.top();
		pq.pop();

		int d = front.first, u = front.second;

		if (d > dist[u])
			continue;

		for (auto a : adjList[u]) {

			if (dist[u] + a.first < dist[a.second]) {
				dist[a.second] = dist[u] + a.first;
				pred[a.second] = u;
				pq.push({dist[a.second], a.second});
			}

		}

	}

	cout << "Case " << numCasos << ": Path = " << ini;

	int node = fin;
	stack<int> s;

	while (node != ini) {
		s.push(node);
		node = pred[node];
	}

	while (!s.empty()) {
		cout << ' ' << s.top();
		s.pop();
	}

	cout << "; " << dist[fin] << " second delay\n";

	return true;

}

int main() {

	while (resuelve()) ++numCasos;

	return 0;

}
