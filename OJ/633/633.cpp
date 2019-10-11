#include <iostream>
#include <queue>

using namespace std;

using ii = pair<int, int>;
using iii = pair<ii, int>;

int f_bishop[] = { -2, -2, 2, 2 };
int c_bishop[] = { -2, 2, 2, -2 };

int f_cab[] = { -2, -1, 1, 2, 2, 1, -1, -2 };
int c_cab[] = { 1, 2, 2, 1, -1, -2, -2, -1 };

const int MAX = 40;
const int INF = 100000;

bool ok(int i, int j, int tam) {

	return i >= 1 && i <= tam && j >= 1 && j <= tam;

}

bool resuelve() {

	int N;

	cin >> N;

	if (N == 0)
		return false;

	int tam = 2 * N;
	ii ini;
	ii fin;
	bool visited[MAX + 1][MAX + 1][3];
	int dist[MAX + 1][MAX + 1][3];

	cin >> ini.first >> ini.second;
	cin >> fin.first >> fin.second;

	ii obs;

	for (int i = 1; i <= MAX; ++i)
		for (int j = 1; j <= MAX; ++j)
			for (int k = 0; k < 3; ++k)
				visited[i][j][k] = false;

	do {

		cin >> obs.first >> obs.second;

		for (int i = 0; i < 3; ++i)
			visited[obs.first][obs.second][i] = true;

	} while (obs.first != 0 || obs.second != 0);	

	for (int i = 0; i < 3; ++i)
		visited[ini.first][ini.second][i] = true;

	for (int i = 1; i <= MAX; ++i)
		for (int j = 1; j <= MAX; ++j)
			for (int k = 0; k < 3; ++k)
				dist[i][j][k] = INF;

	for (int i = 0; i < 3; ++i)
		dist[ini.first][ini.second][i] = 0;

	queue<iii> q;

	q.push({ ini, 3 });

	while (!q.empty() && ini != fin/* && dist[fin.first][fin.second] == 100000*/) {

		iii antonio = q.front();
		q.pop();

		if (antonio.second != 0) {
			for (int i = 0; i < 8; ++i) {
				ii next;
				next.first = antonio.first.first + f_cab[i];
				next.second = antonio.first.second + c_cab[i];

				if (ok(next.first, next.second, tam) && !visited[next.first][next.second][0]) {
					visited[next.first][next.second][0] = true;

					if (antonio.first == ini)
						dist[next.first][next.second][0] = 1;
					else
						dist[next.first][next.second][0] = dist[antonio.first.first][antonio.first.second][antonio.second] + 1;

					q.push({ next,0 });
				}

			}
		}

		if (antonio.second != 1) {
			for (int i = 0; i < 4; ++i) {
				ii next;
				next.first = antonio.first.first + f_bishop[i];
				next.second = antonio.first.second + c_bishop[i];

				if (ok(next.first, next.second, tam) && !visited[next.first][next.second][1]) {
					visited[next.first][next.second][1] = true;
					if (antonio.first == ini)
						dist[next.first][next.second][1] = 1;
					else
						dist[next.first][next.second][1] = dist[antonio.first.first][antonio.first.second][antonio.second] + 1;
					q.push({ next,1 });
				}

			}
		}

		if (antonio.second != 2) {

			ii next;

			next.first = tam + 1 - antonio.first.first;
			next.second = antonio.first.second;


			if (ok(next.first, next.second, tam) && !visited[next.first][next.second][2]) {
				visited[next.first][next.second][2] = true;
				if (antonio.first == ini)
					dist[next.first][next.second][2] = 1;
				else
					dist[next.first][next.second][2] = dist[antonio.first.first][antonio.first.second][antonio.second] + 1;
				q.push({ next,2 });
			}

			next.first = antonio.first.first;
			next.second = tam + 1 - antonio.first.second;

			if (ok(next.first, next.second, tam) && !visited[next.first][next.second][2]) {
				visited[next.first][next.second][2] = true;
				if (antonio.first == ini)
					dist[next.first][next.second][2] = 1;
				else
					dist[next.first][next.second][2] = dist[antonio.first.first][antonio.first.second][antonio.second] + 1;
				q.push({ next,2 });
			}

		}

	}

	int res = min(dist[fin.first][fin.second][0], min(dist[fin.first][fin.second][1], dist[fin.first][fin.second][2]));

	if (res == INF)
		cout << "Solution doesn't exist\n";
	else
		cout << "Result : " << res << '\n';

	return true;

}

int main() {

	while (resuelve());

	return 0;

}
