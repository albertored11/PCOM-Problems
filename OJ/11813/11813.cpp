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
using iii = pair<ii, int>;
using viii = vector<iii>;

const int MAX_INTERSEC = 100000;
const int MAX_STORES = 10;
const int MAX_COMB = 1 << MAX_STORES;
const int INF = 10e6;

vvii adjList;
vector<int> tiendas;
int numInsersec, numCaminos, numTiendas;
int dist[MAX_INTERSEC + 2][MAX_COMB + 2];

void resuelve() {
    
    cin >> numInsersec >> numCaminos;
    
    adjList.assign(numInsersec, vii());
    tiendas.assign(numInsersec, -1);
    
    for (int i = 0; i < numCaminos; ++i) {
    
        int X, Y, D;
        
        cin >> X >> Y >> D;
        
        adjList[X].push_back({D, Y});
        adjList[Y].push_back({D, X});
    
    }
    
    cin >> numTiendas;
    
    for (int i = 0; i < numTiendas; ++i) {
        
        int tienda;
        
        cin >> tienda;
        
        tiendas[tienda] = i;
        
    }
    
    for (int i = 0; i < numInsersec; ++i)
        for (int j = 0; j < (1 << numTiendas); ++j)
            dist[i][j] = INF;
        
    dist[0][0] = 0;
    
    priority_queue<iii, viii, greater<iii>> pq;
    int allVisited = (1 << (numTiendas)) - 1;
    
    pq.push({{0, 0}, 0});
    
    while (!pq.empty()) {
        
        iii front = pq.top();
        pq.pop();
        
        int d = front.first.first;
        int u = front.first.second;
        int visited = front.second;
        
        if (u == 0 && visited == allVisited) {
            cout << dist[0][allVisited] << '\n';
            break;
        }
        
        if (d > dist[u][visited])
            continue;
        
        for (auto a : adjList[u]) {
            
            int newvisited = visited;
            
            if (tiendas[a.second] != -1)
                newvisited |= (1 << tiendas[a.second]);
            
            if (dist[u][visited] + a.first < dist[a.second][newvisited]) {
                dist[a.second][newvisited] = dist[u][visited] + a.first;
                pq.push({{dist[a.second][newvisited], a.second}, newvisited});
            }
            
        }
        
    }

}

int main() {
    
    int nCasos;
    
    cin >> nCasos;
    
    while (nCasos--) resuelve();
    
    return 0;
    
}    
