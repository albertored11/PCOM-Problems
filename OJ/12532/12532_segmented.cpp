#include <iostream>
#include <vector>
#include <string>

using namespace std;

class SegmentTree {

    vector<int> st;
    int tam; // Número de hojas que manejamos

    public:

        // Tamaño máximo que podremos guardar (número de hojas).
        // Antes de las consultas, se necesita rellenar con los datos iniciales usando build().

        SegmentTree(int maxN) {

            st.reserve(4 * maxN + 10);

        }

        int query(int a, int b) {

            return query(1, 0, tam - 1, a, b);

        }

        int query(int vertex, int L, int R, int i, int j) {

            if (i > R || j < L)
                return 0;

            if (L >= i && R <= j)
                // Segmento completamente dentro de la consulta
                return st[vertex];

            int mitad = (L + R) / 2;

            return query(2 * vertex, L, mitad, i, j) * query(2 * vertex + 1, mitad + 1, R, i, j);

        }

        void update(int pos, int newVal) {

            update(1, 0, tam - 1, pos, newVal);

        }

        void update(int vertex, int l, int r, int pos, int newVal) {

            if ((pos < 1) || (r < pos))
                return;

            if (l == r) {

                if (newVal > 0)
                    st[vertex] = 1;
                else if (newVal < 0)
                    st[vertex] = -1;
                else
                    st[vertex] = 0;    

                return;

            }

            int m = (l + r) / 2;

            if ((l <= pos) && (pos <= m))
                update(2 * vertex, l, m, pos, newVal);
            else
                update(2 * vertex + 1, m + 1, r, pos, newVal);

            int val = st[2 * vertex] * st[2 * vertex + 1];

            if (val > 0)
                st[vertex] = 1;
            else if (val < 0)
                st[vertex] = -1;
            else
                st[vertex] = 0;            

        }

        void build(int *values, int n) {

            tam = n;

            build(values, 1, 0, n - 1);

        }

        void build(int *values, int p, int l, int r) {

            if (l == r) {

                if (values[l] > 0)
                    st[p] = 1;
                else if (values[l] < 0)
                    st[p] = -1;
                else
                    st[p] = 0;  
                    
                return;

            }

            int m = (l + r) / 2;

            build(values, 2 * l, l, m);
            build(values, 2 * l + 1, m + 1, r);

            int val = st[2 * l] * st[2 * l + 1];

            if (val > 0)
                st[p] = 1;
            else if (val < 0)
                st[p] = -1;
            else
                st[p] = 0;             

        }

};

bool resuelve() {

    int N;

    cin >> N;

    if (!cin)
        return false;

    int K;

    cin >> K;

    SegmentTree f(N);
    int values[10001];

    for (int i = 0; i < N; ++i)
        cin >> values[i];

    f.build(values, N);

    string operation;

    cin >> operation;

    while (operation != "END") {

        int a, b;

        cin >> a >> b;

        if (operation == "C")
            f.update(a, b);
        else {

            int val = f.query(a, b);

            if (val == 1)
                cout << '+';
            else if (val == -1)
                cout << '-';
            else
                cout << 0;

        }

        cin >> operation;

    }

    return true;

}

int main() {

    while (resuelve());

    return 0;

}
