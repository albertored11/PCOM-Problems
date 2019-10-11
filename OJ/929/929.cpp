#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using ii = pair<int, int>;
using iii = pair<int, ii>;
using viii = vector<iii>;

const int MAX = 1000;
const int INF = 10e6;

int f_mov[] = { -1, 0, 1, 0 };
int c_mov[] = { 0, 1, 0, -1 };

bool ok(int i, int j, int f, int c) {

	return i >= 1 && i <= f && j >= 1 && j <= c;

}

void resuelve() {

	int f, c;
	int maze[MAX][MAX];
	int dist[MAX][MAX];
	priority_queue<iii, viii, greater<iii>> pq;

	cin >> f >> c;

	for (int i = 1; i <= f; ++i) {
		for (int j = 1; j <= c; ++j) {
			cin >> maze[i][j];
			dist[i][j] = INF;
		}
	}

	dist[1][1] = maze[1][1];
	pq.push({maze[1][1], {1, 1}});

	while (pq.top().second != ii(f, c)) {

		iii front = pq.top();
		pq.pop();

		int d = front.first;
		ii actual = front.second;

		if (d > dist[actual.first][actual.second])
			continue;

		for (int i = 0; i < 4; ++i) {

			ii next;

			next.first = actual.first + f_mov[i];
			next.second = actual.second + c_mov[i];

			if (ok(next.first, next.second, f, c) && dist[actual.first][actual.second] + maze[next.first][next.second] < dist[next.first][next.second]) {
				dist[next.first][next.second] = dist[actual.first][actual.second] + maze[next.first][next.second];
				pq.push({dist[next.first][next.second], next});
			}

		}

	}

	cout << dist[f][c] << '\n';

}

int main() {

	int nCasos;

	cin >> nCasos;

	while (nCasos--) resuelve();

	return 0;

}
