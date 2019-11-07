#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <unordered_set>
using namespace std;

using ii = pair<int, int>;
using vb = vector<bool>;
using vi = vector<int>;
using vii = vector<ii>;
using iii = pair<ii, int>;
using viii = vector<iii>;

const int INF = 10e6;
const int MAX_BEEP = 12;
const int MAX_COMB = 4096;

int nCasos;
int X, Y, nBeep;
ii ini;
vii beepers;
int dist[MAX_BEEP][MAX_COMB];

int manhattan(ii a, ii b) {

    return abs(a.first - b.first) + abs(a.second - b.second);

}

bool contiene(ii pos) {

	for (ii bee : beepers)
		if (bee == pos)
			return true;

	return false;

}

void resuelve() {

	int nBeepReal;

    cin >> X >> Y;

    cin >> ini.first >> ini.second >> nBeep;

    beepers.clear();

    beepers.push_back(ini);

    for (int i = 0; i < nBeep; ++i) {

		ii bee;

		cin >> bee.first >> bee.second;

		if (!contiene(bee) && bee != ini)
			beepers.push_back(bee);

    }

    beepers.push_back(ini);

    nBeep = beepers.size() - 2;

    for (int i = 0; i < MAX_BEEP; ++i)
    	for (int j = 0; j < MAX_COMB; ++j)
    		dist[i][j] = INF;

    dist[0][1] = 0;

	priority_queue<iii, viii, greater<iii>> pq;
	int todosRecogidos = (1 << (nBeep + 1)) - 1;
	int final = (1 << (nBeep + 2)) - 1;

    pq.push({{0, 0}, 1});

	while (!pq.empty()) {

		iii front = pq.top();
		pq.pop();

		int d = front.first.first;
		int u = front.second;
		int index = front.first.second;

		if (index == nBeep + 1)
			break;

		if (d > dist[index][u])
			continue;

		if (u == todosRecogidos && dist[index][u] + manhattan(beepers[index], ini) < dist[beepers.size() - 1][final]) {
			dist[beepers.size() - 1][final] = dist[index][u] + manhattan(beepers[index], ini);
			pq.push({{dist[beepers.size() - 1][final], nBeep + 1}, final});
		}

		int visited = u / 2;

		for (int i = 1; i <= nBeep; ++i) {

			ii bind = beepers[index];
			ii bi = beepers[i];

			int manh = abs(bind.first - bi.first) + abs(bind.second - bi.second);

			if (visited % 2 == 0 && dist[index][u] + manh < dist[i][u + (1 << i)]) {
				dist[i][u + (1 << i)] = dist[index][u] + manh;
				pq.push({{dist[i][u + (1 << i)], i}, u + (1 << i)});
			}

			visited /= 2;

		}

	}

	cout << "The shortest path has length " << dist[beepers.size() - 1][final] << '\n';

}


int main() {

    cin >> nCasos;

    while(nCasos--)resuelve();

    return 0;
}