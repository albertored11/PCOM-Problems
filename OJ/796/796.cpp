#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

using ii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vii = vector<ii>;

int hora;
vvi adjList;
vi horaVertice;
vi alcanzable;
vii puentes;

void dfs(int u, int uParent) {

    horaVertice[u] = alcanzable[u] = hora;
    ++hora;

    for (int i = 0; i < adjList[u].size(); ++i) {

        int v = adjList[u][i];

        if (v == uParent)
            continue;

        if (horaVertice[v] == 0) {

            dfs(v, u);

            if (alcanzable[v] > horaVertice[u])
                puentes.push_back({min(u, v), max(u, v)});

            alcanzable[u] = min(alcanzable[u], alcanzable[v]);

        }
        else
            alcanzable[u] = min(alcanzable[u], horaVertice[v]);

    }

}

bool resuelve() {

    int nodos;

    cin >> nodos;

    if (!cin)
        return false;

    adjList.assign(nodos, vi());

    for (int i = 0; i < nodos; ++i) {

        string conexionesStr;
        int nodo, conexiones;

        cin >> nodo;
        cin >> conexionesStr;

        conexionesStr = conexionesStr.substr(1, conexionesStr.length() - 2);
        conexiones = stoi(conexionesStr);

        for (int j = 0; j < conexiones; ++j) {

            int otroNodo;

            cin >> otroNodo;

            adjList[nodo].push_back(otroNodo);

        }

    }

    hora = 1;
    horaVertice.assign(nodos, 0);
    alcanzable.assign(nodos, -1);
    puentes.resize(0);

    for (int i = 0; i < nodos; ++i)
        if (!horaVertice[i])
            dfs(i, 0);

    sort(puentes.begin(), puentes.end());

    cout << puentes.size() << " critical links\n";
    
    for (ii puente : puentes)
        cout << puente.first << " - " << puente.second << '\n';

    cout << '\n';

    return true;

}

int main() {

    while (resuelve());

    return 0;

}
