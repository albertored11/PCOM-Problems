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

int K;

class FenwickTree {

    vector<int> ft;

public:

    FenwickTree(int n) {
        ft.assign(n + 1, 0);
    }

    int getSum(int b) {

        int ret = 0;

        while (b) {
            ret += ft[b];
            b -= (b & -b);
        }

        return ret;

    }

    void add(int pos, int val) {

        while (pos < ft.size()) {
            ft[pos] += val;
            pos += (pos & -pos);
        }

    }

    int getSum(int a, int b) {

        return getSum(b) - getSum(a - 1);

    }

    int getValue(int pos) {

        return getSum(pos) - getSum(pos - 1);

    }

    void setValue(int pos, int val) {

        add(pos, val - getValue(pos));

    }

};

int buscaPos(FenwickTree &tree, int suma, int ini, int fin) {

    int m = (ini + fin) / 2;
    int sum = tree.getSum(m);

    if (sum == suma && tree.getSum(m, m))
        return m;

    if (sum < suma)
        return buscaPos(tree, suma, m + 1, fin);

    return buscaPos(tree, suma, ini, m - 1);

}

int buscaPos(FenwickTree &tree, int suma) {

    return buscaPos(tree, suma, 1, K);

}

void resuelve() {

    cin >> K;

    FenwickTree tree(K);

    for (int i = 1; i <= K; ++i)
        tree.add(i, 1);

    for (int i = 0; i < K; ++i) {

        int si;

        cin >> si;

        int pos = buscaPos(tree, si + 1);

        cout << pos;

        if (i < K - 1)
            cout << ' ';

        tree.add(pos, -1);

    }

    cout << '\n';

}

int main() {

    cin.tie(nullptr);

    int nCasos;

    cin >> nCasos;

    while (nCasos--) resuelve();
    
    return 0;
    
}    
