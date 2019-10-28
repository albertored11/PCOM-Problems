#include <iostream>
#include <cstdio>
#include <climits>
#include <vector>
#include <iomanip>
#include <queue>
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
using vvi = vector<vi>;
using vvii = vector<vii>;
using dii = pair<double, ii>;
using vdii = vector<dii>;
using vd = vector<double>;

vi C;
int numSets;

double dist(pair<double, double> a, pair<double, double> b) {

    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));

}

void init(int n) {
    
    C.assign(n, 0);
    numSets = n;
    
    for (int i = 0; i < n; ++i)
        C[i] = i;

}

int find(int x) {

    return (C[x] == x) ? x : C[x] = find(C[x]);

}

void merge(int x, int y) {
    
    C[find(x)] = find(y);
    --numSets;

}

void resuelve() {

    int numSat, numPuestos;
    vdii aristas;
    vii puestos;

    cin >> numSat >> numPuestos;

    for (int i = 0; i < numPuestos; ++i) {

        ii puesto;

        cin >> puesto.first >> puesto.second;

        for (int j = 0; j < puestos.size(); ++j) {

            double distancia = dist(puesto, puestos[j]);

            aristas.push_back({distancia, {i, j}});
            aristas.push_back({distancia, {j, i}});
            
        }

        puestos.push_back(puesto);

    }

    sort(aristas.begin(), aristas.end());

    init(numPuestos);

    for (dii ar : aristas) {

        if (find(ar.second.first) != find(ar.second.second))
        	merge(ar.second.first, ar.second.second);

        if (numSets == numSat) {

        	cout << fixed << setprecision(2) << ar.first << '\n';

			break;

		}


    }

//    cout << fixed << setprecision(2) << aristasBuenas[] << '\n';

}

int main() {

    int nCasos;

    cin >> nCasos;

    while (nCasos--) (resuelve());

    return 0;

}
