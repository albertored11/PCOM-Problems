#include <iostream>
#include <vector>

using namespace std;

const int MAX = 100005;

class SegmentTree {

	vector<int> st;
	vector<int> lazy;
	int tam; // Número de hojas que manejamos

public:

//	vector<int> st;

	// Tamaño máximo que podremos guardar (número de hojas).
	// Antes de las consultas, se necesita rellenar con los datos iniciales usando build().

	SegmentTree(int maxN) {

		st.reserve(4 * maxN + 10);
		lazy.reserve(4 * maxN + 10);

	}

	void setLazyUpdate(int vertex, int op) {

		// Mezclamos.
		// Importante +=: el nodo podría tener otras operaciones pendientes
		// anteriores.

		lazy[vertex] += op;

	}

	void pushLazyUpdate(int vertex, int L, int R) {

		st[vertex] += (R - L + 1) * lazy[vertex];

		if (L != R) {

			// Tenemos hijos.

			setLazyUpdate(2 * vertex, lazy[vertex]);
			setLazyUpdate(2 * vertex + 1, lazy[vertex]);

		}

		lazy[vertex] = 0;

	}

	int query(int a, int b) {

		return query(1, 0, tam - 1, a, b);

	}

	int query(int vertex, int L, int R, int i, int j) {

		pushLazyUpdate(vertex, L, R);

		if (L >= i && R <= j)
			// Segmento completamente dentro de la consulta
			return st[vertex];

		int mitad = (L + R) / 2;

		if (L <= i && R >= j)
			return query(2 * vertex, L, mitad, i, j) + query(2 * vertex + 1, mitad + 1, R, i, j);

		return 0;

	}

	void updateRange(int a, int b, int op) {

		return updateRange(1, 0, tam - 1, a, b, op);

	}

	void updateRange(int vertex, int l, int r, int a, int b, int op) {

		// Resolvemos posibles operaciones pendientes
		pushLazyUpdate(vertex, l, r);

		if ((b < l) || (r < a))
			return;

		// ¿Intervalo afectado por completo?
		if (a <= l && r <= b) {

			// Nos aplicamos la operación y propagamos la pereza a los hijos.
			// Para evitar copiar/pegar, lo hacemos aplicándonos la pereza,
			// y luego resolviéndola.

			setLazyUpdate(vertex, op);
			pushLazyUpdate(vertex, l, r);

			return;

		}

		// Intervalo no afectado por completo. No podemos ser perezosos.
		// Aplicamos la operación en los hijos.

		int m = (l + r) / 2;

		updateRange(2 * vertex, l, m, a, b, op);
		updateRange(2 * vertex + 1, m + 1, r, a, b, op);

		st[vertex] = st[2 * vertex] + st[2 * vertex + 1];

	}

	void build(int *values, int n) {

		tam = n;

		build(values, 1, 0, n - 1);

	}

	void build(int *values, int p, int l, int r) {

		if (l == r) {

			st[p] = values[l];

			return;

		}

		int m = (l + r) / 2;

		build(values, 2 * p, l, m);
		build(values, 2 * p + 1, m + 1, r);

		st[p] = st[2 * p] + st[2 * p + 1];

	}

};

bool resuelve() {

	int T;

	cin >> T;

	if (!cin)
		return false;

	int edificios[MAX];
	SegmentTree arbol(MAX);

	for (int i = 0; i < MAX; ++i)
		edificios[i] = 0;

	arbol.build(edificios, MAX);

	for (int i = 0; i < T; ++i) {

		char operation;

		cin >> operation;

		if (operation == 'Q') {

			int a;

			cin >> a;

			cout << arbol.query(a, a) << '\n';

		}
		else if (operation == 'B') {

			int a, b, y;

			cin >> a >> b >> y;

			arbol.updateRange(a, b, y);

		}

	}

	return true;

}

int main() {

	while (resuelve());

	return 0;

}
