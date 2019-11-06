#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX_N = 205;
const int INF = 10e6;

using vi = vector<int>;
using vvi = vector<vi>;
using mat = int[MAX_N][MAX_N];

#define in(x) 2 * x
#define out(x) 2 * x + 1
#define source 0
#define sink 1

vvi adjList;
mat cap;
bool visited[MAX_N];
int parent[MAX_N];

int nCaso = 1;

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

	int N;

	cin >> N;

	if (!cin)
		return false;

	int M;
	int B, D;
	int ret, flow;

	adjList.assign(2 * N + 2, vi());

	for (int i = 0; i < MAX_N; ++i)
		for (int j = 0; j < MAX_N; ++j)
			cap[i][j] = 0;

	for (int i = 1; i <= N; ++i) {

		int c;

		adjList[in(i)].push_back(out(i));
		adjList[out(i)].push_back(in(i));

		cin >> c;

		cap[in(i)][out(i)] += c;

	}

	cin >> M;

	for (int i = 0; i < M; ++i) {

		int a, b, c;

		cin >> a >> b;

		adjList[out(a)].push_back(in(b));
		adjList[in(b)].push_back(out(a));

		cin >> c;

		cap[out(a)][in(b)] += c;

	}

	cin >> B >> D;

	for (int i = 0; i < B; ++i) {

		int a;

		cin >> a;

		adjList[source].push_back(in(a));
		adjList[in(a)].push_back(source);

		cap[source][in(a)] = INF;

	}

	for (int i = 0; i < D; ++i) {

		int a;

		cin >> a;

		adjList[out(a)].push_back(sink);
		adjList[sink].push_back(out(a));

		cap[out(a)][sink] = INF;

	}

	ret = 0;
	flow = 0;

	do {
		flow = sendFlow(source, sink);
		ret += flow;
	} while (flow > 0);

	cout << ret << '\n';

	return true;

}

int main() {

	while (resuelve()) ++nCaso;

	return 0;

}
