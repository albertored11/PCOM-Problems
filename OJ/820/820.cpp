#include <iostream>
#include <vector>
#include <cstring>
#include <unordered_set>
#include <queue>
using namespace std;



using vs = vector<unordered_set<int>>;
const int MAX = 101;
int adjMat[MAX][MAX];
const int INF = 10e8;
vs adjList;
int visited[MAX];
int parent[MAX];
int nCasos = 1;

void bfs(int s, int t) {

    queue<int> q;
    memset(visited, 0, sizeof(visited));
    q.push(s);
    parent[s] = -1;
    visited[s] = true;

    while(!q.empty()) {
        int u = q.front();
        q.pop();
        if(u == t) break;
        for(auto v : adjList[u]) {
            if(!visited[v] && (adjMat[u][v] > 0)) {
                parent[v] = u;
                visited[v] = true;
                q.push(v);
            }
        }
    }

}




int sendFlow(int s, int t) {

    bfs(s,t);

    if(!visited[t])
        return 0;

    int flow = INF, v = t;
    
    while(v!= s) {
        flow = min(adjMat[parent[v]][v], flow);
        v = parent[v];
    }

    v = t;
    while(v != s) {
        adjMat[parent[v]][v] -= flow;
        adjMat[v][parent[v]] += flow;
        v = parent[v];
    }


    return flow;
}



bool resuelve() {

    int n;

    cin >> n;

    if(n == 0)
        return false;

    int source , destination , c;
    adjList.assign(n + 1, unordered_set<int>());
    memset(adjMat, 0, MAX * MAX * sizeof(int));

    cin >> source >> destination >> c;

    for (int i = 0; i < c; ++i) {

        int a, b, tam;

        cin >> a >> b >> tam;

        adjList[a].emplace(b);
        adjList[b].emplace(a);

        adjMat[a][b] += tam;
        adjMat[b][a] += tam;
    }

    int maxFlow = 0, flow = 0;

    do {
        flow = sendFlow(source,destination);
        maxFlow += flow;
    } while (flow > 0);

    cout << "Network " << nCasos << '\n';
    cout << "The bandwidth is " << maxFlow << ".\n\n";

    return true;
}


int main() {



    while(resuelve())++nCasos;;



    return 0;
}