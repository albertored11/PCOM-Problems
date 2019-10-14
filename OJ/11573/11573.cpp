#include <iostream>
#include <queue>
#include <string>

using namespace std;

using ii = pair<int, int>;

const int MAX = 1000;
const int INF = 10000000;

int f_rey[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int c_rey[] = { 0, 1, 1, 1, 0, -1, -1, -1 };

int f, c;
int grid[MAX + 1][MAX + 1];

bool ok(int i, int j) {

	return i >= 1 && i <= f && j >= 1 && j <= c;

}

void resuelve() {

	ii ini;
	ii fin;
	int dist[MAX + 1][MAX + 1];
	deque<ii> q;

	cin >> ini.first >> ini.second >> fin.first >> fin.second;

	for (int i = 1; i <= f; ++i)
		for (int j = 1; j <= c; ++j)
			dist[i][j] = INF;

	dist[ini.first][ini.second] = 0;
	q.push_back(ini);

	while (!q.empty() && q.front() != fin) {

		ii actual = q.front();
		q.pop_front();

		for (int i = 0; i < 8; ++i) {

			ii next;

			next.first = actual.first + f_rey[i];
			next.second = actual.second + c_rey[i];

			if (i != grid[actual.first][actual.second]) {
				if (ok(next.first, next.second) && dist[actual.first][actual.second] + 1 < dist[next.first][next.second]) {
					q.push_back(next);
					dist[next.first][next.second] = dist[actual.first][actual.second] + 1;
				}
			}
			else {
				if (ok(next.first, next.second) && dist[actual.first][actual.second] < dist[next.first][next.second]) {
					q.push_front(next);
					dist[next.first][next.second] = dist[actual.first][actual.second];
				}
			}

		}

	}

	cout << dist[fin.first][fin.second] << '\n';

}

int main() {

	int nCasos;

	while (cin >> f >> c) {

		for (int i = 1; i <= f; ++i) {

			string line;

			cin >> line;

			for (int j = 1; j <= c; ++j)
				grid[i][j] = line[j - 1] - '0';

		}

		cin >> nCasos;

		while (nCasos--) resuelve();

	}

	return 0;

}
