#include <iostream>
#include <cstdio>
#include <climits>
#include <vector>
#include <iomanip>
#include <queue> // Cola de mayor a menor por defecto en priority
#include <algorithm>
#include <cstring>
#include <cmath>
#include <string>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <unordered_map>
#include <deque>
#include <unordered_set>

using namespace std;

using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
using vvi = vector<vi>; // para listas de adyacencia
using vvii = vector<vii>;
using iiii = pair<ii, ii>;
using viiii = vector<iiii>;

const int INF = 10e6;


void resuelve() {

    int pueblos, castillos, caminos, distMax, numUsos;
    vvii adjList;
    int dist[110][12];


    cin >> pueblos >> castillos >> caminos >> distMax >> numUsos;

    adjList.assign(pueblos + castillos + 1, vii());

    for (int i = 1; i < pueblos + castillos + 1; ++i)
        for (int j = 0; j <= numUsos; ++j)
            dist[i][j] = INF;

    for (int i = 0; i < caminos; ++i) {

        int x, y, l;

        cin >> x >> y >> l;

        adjList[x].push_back({l, y});
        adjList[y].push_back({l, x});
    }

    dist[pueblos + castillos][numUsos] = 0;

    priority_queue<iiii, viiii, greater<iiii>> pq;
    pq.push({{0, pueblos + castillos}, {numUsos, 0}});

    while (!pq.empty()) {

        iiii front = pq.top();
        pq.pop();
        int d = front.first.first;
        int u = front.first.second;
        int usos = front.second.first;
        int distBotas = front.second.second;

        /*if (u == 1) {
            cout << d << '\n';
            return;
        }*/
        if (d > dist[u][usos]) continue;
        for (auto a : adjList[u]) {
            if (distBotas > 0 || usos > 0) {
                    if (a.first + distBotas <= distMax) {
                        if (distBotas > 0 && u <= pueblos && dist[u][usos] < dist[a.second][usos]) {
                            dist[a.second][usos] = dist[u][usos];
                            pq.push({{dist[a.second][usos], a.second},{usos, distBotas + a.first}});
                        }
                        else if (usos > 0 && dist[u][usos] < dist[a.second][usos - 1]) {
                            dist[a.second][usos - 1] = dist[u][usos];
                            pq.push({{dist[a.second][usos - 1], a.second},{usos - 1, a.first}});
                        }
                    }
            }
            if (dist[u][usos] + a.first < dist[a.second][usos]){
                dist[a.second][usos] = dist[u][usos] + a.first;
                pq.push({{dist[a.second][usos], a.second}, {usos, 0}});
            }

        }
    }

}


int main() {

    int nCasos;

    cin >> nCasos;

    while(nCasos--) resuelve();
    
    return 0;
    
}    
