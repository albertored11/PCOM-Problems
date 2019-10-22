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

int f_mov[] = {-1, 0, 1, 0};
int c_mov[] = {0, 1, 0, -1};


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

    int X;

    cin >> X;

    if(!cin)
        return false;
    
    int Y, P;
    string tablero[MAX];

    cin >> Y >> P;

    for (int i = 0; i < X; ++i)
        cin >> tablero[i];
    
    adjList.assign(X * Y * 2 + 2, vi());

    for (int i = 0; i < X; ++i)
        for (int j = 0; j < Y; ++j) {
            char square = tablero[i][j];
            if (square != '~') {

                if (square == '*') {
                    adjList[2*X*Y].push_back(2*Y*i + 2*j);
                    adjList[2*Y*i + 2*j].push_back(2*Y*i + 2*j + 1);
                    cap[2*X*Y][2*Y*i + 2*j] = 1;
                    cap[2*Y*i + 2*j][2*Y*i + 2*j+1] = 1;
                }

                if (square == '.') {
                    adjList[2*Y*i + 2*j].push_back(2*Y*i + 2*j + 1);
                    cap[2*Y*i + 2*j][2*Y*i + 2*j+1] = 1;
                }

                if (square == '@') {
                    adjList[2*Y*i + 2*j].push_back(2*Y*i + 2*j + 1);
                    cap[2*Y*i + 2*j][2*Y*i + 2*j+1] = INF;
                }

                if (square == '#') {
                    adjList[2*Y*i + 2*j + 1].push_back(2*X*Y + 1);
                    cap[2*Y*i + 2*j + 1][2*X*Y + 1] = P;
                    adjList[2*Y*i + 2*j].push_back(2*Y*i + 2*j + 1);
                    cap[2*Y*i + 2*j][2*Y*i + 2*j + 1] = INF;
                }

                for (int k = 0; k < 4; ++k) {
                    ii next = {i, j};
                    next.first += f_mov[k];
                    next.second += c_mov[k];

                    if (inBounds(X, Y, next) && tablero[next.first][next.second] != '~' && tablero[next.first][next.second] != '*') {
                        adjList[2*Y*i + 2*j + 1].push_back(2*Y*next.first + 2*next.second);
                        cap[2*Y*i + 2*j + 1][2*Y*next.first + 2*next.second] = INF;
                    }
                }

            }
        }

    int ret = 0, flow = 0;

    do {
        flow = sendFlow(2*X*Y, 2*X*Y + 1);
        ret += flow;
    } while(flow > 0);

    cout << ret << '\n';

    return true;
}



int main() {

    while(resuelve());


    return 0;
}