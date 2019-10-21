#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <cstring>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using vs = vector<string>;
using vus = vector<unordered_set<int>>;
const int MAX_VERT = 25;

vs nombres;
vus adjList;
unordered_map<string, int> code;
vi horaVertice;
vi alcanzable;
bool incurrentscc[MAX_VERT];
int hora;
vi sccstack;
int nCasos = 1;


void scc(int u) {

    horaVertice[u] = alcanzable[u] = hora;
    ++hora;
    incurrentscc[u] = true;
    sccstack.push_back(u);

    for (auto v : adjList[u]) {
        
        if (!horaVertice[v])
            scc(v);
        if(incurrentscc[v])
            alcanzable[u] = min(alcanzable[u], alcanzable[v]);
    }

    if (horaVertice[u] == alcanzable[u]) {
        vi sc;
        int v;
        bool first = true;

        do {
            v = sccstack.back();
            sccstack.pop_back();
            sc.push_back(v);
            incurrentscc[v] = false;
            
            if (!first)
                cout << ", ";
            else
                first = false;
            
            cout << nombres[v];
        } while (u != v);

        cout << '\n';

    }


}



bool resuelve() {

    int n, m;

    cin >> n >> m;

    if (n == 0 && m == 0)
        return false;

    code.clear();
    adjList.assign(n, unordered_set<int>());
    nombres.clear();

    for (int i = 0; i < m; ++i) {

        string a, b;

        cin >> a >> b;

        if (code.count(a) == 0) {
            code.emplace(a, nombres.size());
            nombres.push_back(a);
        }
        if (code.count(b) == 0) {
            code.emplace(b, nombres.size());
            nombres.push_back(b);
        }
        adjList[code.at(a)].emplace(code.at(b));
    }

    horaVertice.assign(n, 0);
    alcanzable.assign(n, -1);
    memset(incurrentscc, 0, sizeof(incurrentscc));
    sccstack.clear();
    hora = 1;

    if (nCasos > 1)
        cout << '\n';

    cout << "Calling circles for data set " << nCasos << ":\n";

    for (int i = 0; i < n; ++i)
        if(!horaVertice[i])
            scc(i);


    return true;
}




int main() {


    while (resuelve()) ++nCasos;

    return 0;
}