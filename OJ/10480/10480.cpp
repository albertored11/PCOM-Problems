#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX_N = 55;
const int INF = 10e6;

using vi = vector<int>;
using vvi = vector<vi>;
using mat = int[MAX_N][MAX_N];

vvi adjList;
mat cap;
bool visited[MAX_N];
int parent[MAX_N];

void bfs(int s, int t) {

	queue<int> q;

	for (int i = 0; i < MAX_N; ++i)
		visited[i] = false;

	q.push(s);

	parent[s] = -1;
	visited[s] = true;

	while (!q.empty()) {

		int u = q.front();
		q.pop();

		if (u == t)
			break;

		for (int i = 0; i < adjList[u].size(); ++i) {

			int v = adjList[u][i];

			if (!visited[v] && cap[u][v] > 0) {
				parent[v] = u;
				visited[v] = true;
				q.push(v);
			}

		}

	}

}

int sendFlow(int s, int t) {

	bfs(s, t);

	if (!visited[t])
		return 0;

	int flow = INF, v = t;

	while (v != s) {
		flow = min(cap[parent[v]][v], flow);
		v = parent[v];
	}

	v = t;

	while (v != s) {
		cap[parent[v]][v] -= flow;
		cap[v][parent[v]] += flow;
		v = parent[v];
	}

	return flow;

}

bool resuelve() {

	int numCities, numConnections;

	cin >> numCities >> numConnections;

	if (numCities == 0 && numConnections == 0)
		return false;

	int source = numCities + 1;
	int sink = source + 1;
	int ret, flow;

	adjList.assign(numCities + 3, vi());

	for (int i = 0; i < MAX_N; ++i)
		for (int j = 0; j < MAX_N; ++j)
			cap[i][j] = 0;

	for (int i = 0; i < numConnections; ++i) {

		int a, b;

		cin >> a >> b;

		adjList[a].push_back(b);
		adjList[b].push_back(a);

		cin >> cap[a][b];
		cap[b][a] = cap[a][b];

	}

	adjList[source].push_back(1);
	adjList[1].push_back(source);

	cap[source][1] = INF;
	cap[1][source] = INF;

	adjList[2].push_back(sink);
	adjList[sink].push_back(2);

	cap[2][sink] = INF;
	cap[sink][2] = INF;

	ret = 0;
	flow = 0;

	do {
		flow = sendFlow(source, sink);
		ret += flow;
	} while (flow > 0);

	for (int i = 1; i < numCities + 3; ++i)
		if (visited[i])
			for (int a : adjList[i])
				if (!visited[a])
					cout << i << ' ' << a << '\n';

	cout << '\n';

	return true;

}

int main() {

	while (resuelve());

	return 0;

}
