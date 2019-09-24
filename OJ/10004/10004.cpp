#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool resuelve() {

	int nodes;

	cin >> nodes;

	if (nodes == 0)
		return false;

	int edges;
	vector<vector<int>> adjList(200);
	vector<int> color(200);

	cin >> edges;

	for (int i = 0; i < edges; ++i) {

		int x, y;

		cin >> x >> y;

		adjList[x].push_back(y);
		adjList[y].push_back(x);

	}

	for (int i = 0; i < 200; ++i)
		color[i] = -1;

	bool coloreable = true;
	queue<int> q;

	q.push(0);
	color[0] = 0;

	while (!q.empty() && coloreable) {

		int node = q.front();
		q.pop();

		for (int node1 : adjList[node]) {

			if (color[node1] == -1) {
				color[node1] = (color[node] + 1) % 2;
				q.push(node1);
			}
			else if (color[node1] == color[node]) {
				coloreable = false;
				break;
			}

		}

	}

	if (coloreable)
		cout << "BICOLORABLE.\n";
	else
		cout << "NOT BICOLORABLE.\n";

	return true;

}

int main() {

	while (resuelve());

	return 0;

}
