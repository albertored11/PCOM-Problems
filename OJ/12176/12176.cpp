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
using iii = pair<int, ii>;
using viii = vector<iii>;
using vb = vector<bool>;

int caso;

vector<int> C; int numSets;
void init(int n) {
 C.assign(n, 0); numSets = n;
 for (int i = 0; i < n; ++i) C[i] = i;
}
int find(int x) {
 return (C[x] == x) ? x : C[x] = find(C[x]);
}
void merge(int x, int y) { // find(x) != find(y)
 C[find(x)] = find(y);
 --numSets;
} 

vvii adjList;
vb visited;

void resuelve() {

    int N, R;

    cin >> N >> R;

    adjList.assign(N + 1, vii());
    viii aristas(R);

    for (int i = 0; i < R; ++i) {

        int a, b, l;

        cin >> a >> b >> l;

//        adjList[a].push_back({b, l});
//        adjList[l].push_back({a, l});

        aristas.push_back({l, {a, b}});        

    }

    sort(aristas.begin(), aristas.end());

    init(N + 1);

    for (auto ar : aristas) {

        if (find(ar.second.first) != find(ar.second.second)) {
            merge(ar.second.first, ar.second.second);
            adjList[ar.second.first].push_back({ar.second.second, ar.first});
            adjList[ar.second.second].push_back({ar.second.first, ar.first});
        }

        if (numSets == 1) break;

    }

    int Q;

    cin >> Q;

    cout << "Case " << caso << '\n';

    for (int i = 0; i < Q; ++i) {

        int a, b;

        cin >> a >> b;

        visited.assign(N + 1, false);

        queue<ii> q;
        visited[a] = true;
        q.push({a, 0});

        while (!q.empty()) {

            ii v = q.front(); q.pop();

            if (v.first == b) {
                cout << v.second << '\n';
                break;
            }

            for (ii w : adjList[v.first])
                if (!visited[w.first]) {
                    visited[w.first] = 1;
                    q.push({w.first, max(v.second, w.second)});
                }

        }

    }      

    cout << '\n';

}

int main() {

    int nCasos;

    cin >> nCasos;

    for (caso = 1; caso <= nCasos; ++caso)
        resuelve();
    
    return 0;
    
}    
