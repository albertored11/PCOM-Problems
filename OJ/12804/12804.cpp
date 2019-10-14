#include <iostream>
#include <vector>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

// buscar ciclos

void resuelve() {

	int lines;
	bool termina = false;
	char ins;

	cin >> lines;

	vvi adjList(lines + 1);

	for (int i = 0; i < lines; ++i) {

		cin >> ins;

		if (ins == 'A' || ins == 'C')
			adjList[i].push_back(i + 1);

		if (ins == 'J' || ins == 'C') {

			int next;

			cin >> next;

			if (next > lines)
				termina = true;

			adjList[i].push_back(next);

		}

	}

	if (ins == 'A')
		termina = true;

}

int main() {

	int nCasos;

	cin >> nCasos;

	while (nCasos--) resuelve();

	return 0;

}
