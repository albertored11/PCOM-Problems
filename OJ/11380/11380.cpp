#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

const int MAX = 31;
const int INF = 10e6;

using vi = vector<int>;
using vvi = vector<vi>;
using ii = pair<int, int>;

bool visited[MAX * MAX * 2];
int parent[MAX * MAX * 2];
int cap[MAX * MAX * 2 ][MAX * MAX * 2];
vvi adjList;
int X, Y, P;

int f_mov[] = {-1, 0, 1, 0};
int c_mov[] = {0, 1, 0, -1};

#define in(x, y) 2*Y*x + 2*y
#define out(x, y) 2*Y*x + 2*y + 1
#define source 2*X*Y
#define sink 2*X*Y + 1

void addArista(int u, int v, int capac) {

	if (!cap[u][v] && !cap[v][u]) {
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}

	cap[u][v] += capac;

}

bool inBounds (int f, int c, ii square) {
    return square.first >= 0 && square.first < f && square.second >= 0 && square.second < c;
}

void bfs(int s, int t) {

    queue<int> q;
    for (int i = 0; i < MAX * MAX * 2; ++i)
        visited[i] = false;
    q.push(s);
    parent[s] = -1; visited[s] = true;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == t) break;
        for (int i = 0; i < adjList[u].size(); ++i) {
            int v = adjList[u][i];
            if(!visited[v] && (cap[u][v] > 0)) {
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

    cin >> X;

    if(!cin)
        return false;

    string tablero[MAX];

    cin >> Y >> P;

    for (int i = 0; i < X; ++i)
        cin >> tablero[i];
    
    adjList.assign(X * Y * 2 + 2, vi());

    for (int i = 0; i < X * Y * 2 + 2; ++i)
		for (int j = 0; j < X * Y * 2 + 2; ++j)
			cap[i][j] = 0;

    for (int i = 0; i < X; ++i)
        for (int j = 0; j < Y; ++j) {
            char square = tablero[i][j];
            if (square != '~') {

                if (square == '*') {
                	addArista(source, in(i, j), 1);
                	addArista(in(i, j), out(i, j), 1);
                }

                if (square == '.')
					addArista(in(i, j), out(i, j), 1);

                if (square == '@')
					addArista(in(i, j), out(i, j), INF);

                if (square == '#') {
					addArista(in(i, j), out(i, j), INF);
					addArista(out(i, j), sink, P);
                }

                for (int k = 0; k < 4; ++k) {
                    ii next = {i, j};
                    next.first += f_mov[k];
                    next.second += c_mov[k];

                    if (inBounds(X, Y, next) && tablero[next.first][next.second] != '~' && tablero[next.first][next.second] != '*')
                    	addArista(out(i, j), in(next.first, next.second), INF);
                }

            }
        }

    int ret = 0, flow = 0;

    do {
        flow = sendFlow(source, sink);
        ret += flow;
    } while(flow > 0);

    cout << ret << '\n';

    return true;
}



int main() {

    while(resuelve());


    return 0;
}