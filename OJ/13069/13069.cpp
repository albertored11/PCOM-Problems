#include <iostream>
#include <queue>

using namespace std;

const int MAX = 10000;
const int INF = 100000;

bool resuelve() {

	int a;

	cin >> a;

	if (!cin)
		return false;

	int b;
	bool visited[MAX];
	int dist[MAX];
	queue<int> q;

	cin >> b;

	for (int i = 0; i < MAX; ++i)
		visited[i] = false;

	for (int i = 0; i < MAX; ++i)
		dist[i] = 0;

	visited[a] = true;
	q.push(a);

	if (a != b) {

		while (dist[b] == 0) {

			int v = q.front();
			q.pop();

			int w = (v + 1) % MAX;

			if (!visited[w]) {
				dist[w] = dist[v] + 1;
				visited[w] = true;
				q.push(w);
			}

			w = (v * 2) % MAX;

			if (!visited[w]) {
				dist[w] = dist[v] + 1;
				visited[w] = true;
				q.push(w);
			}

			w = (v / 3) % MAX;

			if (!visited[w]) {
				dist[w] = dist[v] + 1;
				visited[w] = true;
				q.push(w);
			}

		}

	}

	cout << dist[b] << '\n';

	return true;

}

int main() {

	while (resuelve());

	return 0;

}
