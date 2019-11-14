#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
using vvii = vector<vii>;
using iii = pair<int, ii>;
using viii = vector<iii>;

const int INF = 10e8;
const int MAX_CAP = 102;
const int MAX_CITIES = 1002;

int numCities, numRoads;
vi prices;
vvii adjList;
int numCasos;
int dist[MAX_CAP][MAX_CITIES];

void resuelve() {

	int cap, start, end;

	cin >> cap >> start >> end;

	if (adjList[end].empty()) {
		cout << "impossible\n";
		return;
	}

	for (int i = 0; i <= cap; ++i)
		for (int j = 0; j < numCities; ++j)
			dist[i][j] = INF;

	dist[0][start] = 0;

	priority_queue<iii, viii, greater<iii>> pq;

	pq.push({0, {0, start}});

	while (!pq.empty()) {

		iii front = pq.top();
		pq.pop();

		if (front.second.second == end) {
			cout << front.first << '\n';
			return;
		}

		int d = front.first;
		int comb = front.second.first;
		int u = front.second.second;

		if (d > dist[comb][u])
			continue;

        if (comb < cap && dist[comb][u] + prices[u] < dist[comb + 1][u]) {
            dist[comb + 1][u] = dist[comb][u] + prices[u];
            pq.push({dist[comb + 1][u], {comb + 1, u}});
        }

		for (auto a : adjList[u]) {

			if (comb >= a.first && dist[comb][u] < dist[comb - a.first][a.second]) {
                dist[comb - a.first][a.second] = dist[comb][u];
                pq.push({dist[comb - a.first][a.second], {comb - a.first, a.second}});
			}

		}

	}

	cout << "impossible\n";

}

int main() {

    cin >> numCities >> numRoads;

    for (int i = 0; i < numCities; ++i) {

		int pr;

		cin >> pr;

		prices.push_back(pr);

	}

	adjList.assign(numCities, vii());

	for (int i = 0; i < numRoads; ++i) {

		int u, v, d;

		cin >> u >> v >> d;

		adjList[u].push_back({d, v});
		adjList[v].push_back({d, u});

	}

	cin >> numCasos;

	while (numCasos--) resuelve();

	return 0;

}
