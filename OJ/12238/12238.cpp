#include <iostream>
#include <vector>

using namespace std;

using vi = vector<long long int>;
using vvi = vector<vi>;

vi dist;
vvi adjList;
vi euler;
vi prof;
vi first;

class SegmentTree {

    vector<long long int> st;
    long long int tam; // Número de hojas que manejamos

public:

    // Tamaño máximo que podremos guardar (número de hojas).
    // Antes de las consultas, se necesita rellenar con los datos iniciales usando build().

    SegmentTree(long long int maxN) {

        st.reserve(4 * maxN + 10);

    }

    long long int query(long long int a, long long int b) {

        return query(1, 0, tam - 1, a, b);

    }

    long long int query(long long int vertex, long long int L, long long int R, long long int i, long long int j) {

        if (i > R || j < L)
            return -1;

        if (L >= i && R <= j)
            // Segmento completamente dentro de la consulta
            return st[vertex];

        long long int mitad = (L + R) / 2;

        long long int q1 = query(2 * vertex, L, mitad, i, j);
        long long int q2 = query(2 * vertex + 1, mitad + 1, R, i, j);

        if (q1 == -1)
            return q2;
        else if (q2 == -1)
            return q1;

        return (prof[q1] < prof[q2]) ? q1 : q2;

    }

    void build(long long int *values, long long int n) {

        tam = n;

        build(values, 1, 0, n - 1);

    }

    void build(long long int *values, long long int p, long long int l, long long int r) {

        if (l == r) {
            st[p] = l;
            return;
        }

        long long int m = (l + r) / 2;

        build(values, 2 * p, l, m);
        build(values, 2 * p + 1, m + 1, r);

        if (values[st[2 * p]] < values[st[2 * p + 1]])
            st[p] = st[2 * p];
        else
            st[p] = st[2 * p + 1];

    }

};

void dfs(long long int v, long long int p) {

    euler.push_back(v);
    prof.push_back(p);

    if (first[v] == -1)
        first[v] = euler.size() - 1;

    for (long long int w : adjList[v]) {
        dfs(w, p + 1);
        euler.push_back(v);
        prof.push_back(p);
    }

}

bool resuelve() {

    long long int numHormigueros;

    cin >> numHormigueros;

    if (numHormigueros == 0)
        return false;

    long long int numQueries;

    adjList.assign(numHormigueros, vi());
    dist.assign(numHormigueros, 0);

    for (long long int i = 1; i < numHormigueros; ++i) {

        long long int conexion, longitud;

        cin >> conexion >> longitud;

        dist[i] = dist[conexion] + longitud;

//        adjList[i].push_back(conexion);
        adjList[conexion].push_back(i);

    }

    first.assign(numHormigueros, -1);

    dfs(0, 0);

    SegmentTree tree(prof.size());

    tree.build(prof.data(), prof.size());

    cin >> numQueries;

    for (long long int i = 0; i < numQueries; ++i) {

        long long int inicio, fin;

        cin >> inicio >> fin;

        long long int inicioQ = first[inicio];
        long long int finQ = first[fin];

        if (finQ < inicioQ)
            swap(inicioQ, finQ);

        long long int lca = euler[tree.query(inicioQ, finQ)];

        cout << dist[inicio] + dist[fin] - 2 * dist[lca];

        if (i < numQueries - 1)
            cout << ' ';

    }

    cout << '\n';

    return true;

}

int main() {

    while (resuelve());

    return 0;

}
