#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <queue>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using ib = pair<int, bool>;
using ibi = pair<ib, int>;
using vibi = vector<ibi>;
using vvibi = vector<vibi>;
using ii = pair<int, int>;
using iii = pair<ii, int>;
using viii = vector<iii>;

const int INF = 10e6;

void resuelve() {

    int numCities, start, dest, maxPlanes, numTrainRoutes, numPlaneRoutes;
    vvibi adjList;

    cin >> numCities;
    cin >> start >> dest;
    cin >> maxPlanes;

    adjList.assign(numCities, vibi());

    cin >> numTrainRoutes;
    
    for (int i = 0; i < numTrainRoutes; ++i) {

        int cityStart;
        ibi route;

        cin >> cityStart >> route.second >> route.first.first;

        route.first.second = false;

        adjList[cityStart].push_back(route);
        
        int aux = cityStart;
        cityStart = route.second;
        route.second = aux;

        adjList[cityStart].push_back(route);

    }

    cin >> numPlaneRoutes;

    for (int i = 0; i < numPlaneRoutes; ++i) {
        
        int cityStart;
        ibi route;

        cin >> cityStart >> route.second >> route.first.first;

        route.first.second = true;

        adjList[cityStart].push_back(route);
        
        int aux = cityStart;
        cityStart = route.second;
        route.second = aux;

        adjList[cityStart].push_back(route);

    }

    vi dist;

    dist.assign(adjList.size(), INF);
    dist[start] = 0;
    
    priority_queue<iii, viii, greater<iii>> pq;

    pq.push({{0, start}, maxPlanes});

    while (!pq.empty() /*&& pq.top().first.second != dest*/) {

        iii front = pq.top();
        pq.pop();

        int d = front.first.first, u = front.first.second;

        if (d > dist[u])
            continue;

        for (auto a : adjList[u]) {

            if (dist[u] + a.first.first < dist[a.second]) {

                if (a.first.second) {
                    if (front.second > 0) {
                        dist[a.second] = dist[u] + a.first.first;
                        pq.push({{dist[a.second], a.first.second}, front.second - 1});
                    }
                }
                else {
                        dist[a.second] = dist[u] + a.first.first;
                        pq.push({{dist[a.second], a.first.second}, front.second});
                }               

            }

        }

    }

    cout << dist[dest] << '\n';

}

int main() {

	int nCasos;

    cin >> nCasos;

    while (nCasos--) (resuelve());

}
