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

int busca(vi &vec, int elem, int ini, int fin) {

    int m = (ini + fin) / 2;

    if (fin < ini)
        return ini;

    if (vec[m] == elem)
        return -1;

    if (vec[m] < elem)
        return busca(vec, elem, m + 1, fin);

    return busca(vec, elem, ini, m - 1);

}

int busca(vi &vec, int elem) {

    return busca(vec, elem, 0, vec.size() - 1);

}

bool resuelve() {

    int N;

    cin >> N;

    if (!cin)
        return false;

    vi wario;
    vi lis;
    vi maxI;
    int maxWario = 0;

    for (int i = 0; i < N; ++i) {

        int n;

        cin >> n;

        wario.push_back(n);

    }

    lis.push_back(wario.front());
    maxI.push_back(lis.size());

    for (int i = 1; i < N; ++i) {

        if (wario[i] > lis.back())
            lis.push_back(wario[i]);
        else {

            int pos = busca(lis, wario[i]);

            if (pos != -1)
                lis[pos] = wario[i];

        }

        maxI.push_back(lis.size());

    }

    lis.clear();

    for (int i = N - 1; i >= 0; --i) {

        if (wario[i] > lis.back())
            lis.push_back(wario[i]);
        else {

            int pos = busca(lis, wario[i]);

            if (pos != -1)
                lis[pos] = wario[i];

        }

        int semiTam = min((int)lis.size(), maxI[i]);

        maxWario = max(maxWario, 2 * semiTam - 1);

    }

    cout << maxWario << '\n';

    return true;

}

int main() {

    while (resuelve());
    
    return 0;
    
}    
