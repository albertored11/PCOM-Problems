#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int MAX = 100;
const int INF = 10e6;

int f, c;

int f_cab[] = {-1, -2, -2, -1, 1, 2, 2, 1};
int c_cab[] = {-2, -1, 1, 2, 2, 1, -1, -2};

int f_rey[] = {-1, -1, -1, 0, 1, 1, 1, 0};
int c_rey[] = {-1, 0, 1, 1, 1, 0, -1, -1};

bool ok(int i, int j) {

	return i >= 0 && i < f && j >= 0 && j < c;

}

void resuelve() {

	bool visited[MAX + 1][MAX + 1];
	pair<int, int> A, B;
	queue<pair<int, int>> q;
	int dist[MAX + 1][MAX + 1];

	cin >> f >> c;

	for (int i = 0; i < f; ++i)
		for (int j = 0; j < c; ++j)
			visited[i][j] = false;

	for (int i = 0; i < f; ++i) {
		for (int j = 0; j < c; ++j) {

			char square;

			cin >> square;

			if (square == 'Z') {

				visited[i][j] = true;

				for (int k = 0; k < 8; ++k)
					if (ok(i + f_cab[k], j + c_cab[k]))
						visited[i + f_cab[k]][j + c_cab[k]] = true;

			}
			else if (square == 'A') {
				A.first = i;
				A.second = j;
			}
			else if (square == 'B') {
				B.first = i;
				B.second = j;
			}

		}
	}

	visited[A.first][A.second] = true;
	visited[B.first][B.second] = false;

	for (int i = 0; i < f; ++i)
		for (int j = 0; j < c; ++j)
			dist[i][j] = INF;

	q.push(A);
	bool fin = false;


	while (!q.empty() && !fin) {

		pair<int, int> square = q.front();
		q.pop();

		for (int k = 0; k < 9; ++k) {
			int ni, nj;
			ni = square.first + f_rey[k];
			nj = square.second + c_rey[k];
			pair<int, int> ns(ni, nj);

			if (ok(ni, nj) && !visited[ni][nj]) {

				visited[ni][nj] = true;

				q.push(ns);

				if (ns.first == B.first && ns.second == B.second) {
					fin = true;
					break;
				}

			}

		}

	}

	if (q.empty())
		cout << "King Peter, you can't go now!\n";
	else
		cout << "Minimal possible length of a trip is " << '\n';


}

int main() {

	int numC;

	cin >> numC;

	while(numC--) resuelve();


	return 0;
}