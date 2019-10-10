#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

using ii = pair<int, int>;
using iii = pair<int, ii>;
using viii = vector<iii>;

const int INF = 100000;
const int MAX = 201;

void resuelve() {

	int a, b, c, d;

	cin >> a >> b >> c >> d;

	if (d >= c) {
		cout << 0 << ' ' << c << '\n';
		return;
	}

	int dist[MAX][MAX];
	priority_queue<iii, viii, greater<iii>> pq;
	int dPrima = 0;
	int mejorCoste = 0;
	int first, second, third;
//	bool donete = false;

//	memset(dist, INF, MAX * MAX * sizeof(int));

	for (int i = 0; i < c; ++i)
		for (int j = 0; j < c; ++j)
			dist[i][j] = INF;

	dist[0][0] = 0;
	pq.push({0, {0, 0}});

	while (!pq.empty()/* && !donete*/) {

		iii front = pq.top();
		pq.pop();

		int D = front.first;
		ii u = front.second;

		if (dPrima == d)
			break;

		first = u.first;
		second = u.second;
		third = c - (first + second);

		if (first > dPrima && first <= d) {
			dPrima = first;
			mejorCoste = dist[first][second];
		}

		if (second > dPrima && second <= d) {
			dPrima = second;
			mejorCoste = dist[first][second];
		}

		if (third > dPrima && third <= d) {
			dPrima = third;
			mejorCoste = dist[first][second];
		}

		if (D > dist[u.first][u.second])
			continue;

		if (first > 0) {

			if (second < b) {

				int coste = min(b - second, first);

				first -= coste;
				second += coste;

				if (dist[u.first][u.second] + coste < dist[first][second]) {

					dist[first][second] = dist[u.first][u.second] + coste;



					pq.push({dist[first][second], {first, second}});

				}

				first += coste;
				second -= coste;

			}

			if (third < c) {

				int coste = min(c - third, first);

				first -= coste;
				third += coste;

				if (dist[u.first][u.second] + coste < dist[first][second]) {

					dist[first][second] = dist[u.first][u.second] + coste;


					pq.push({dist[first][second], {first, second}});

				}

				first += coste;
				third -= coste;

			}

		}

		if (second > 0) {

			if (first < a) {

				int coste = min(a - first, second);

				second -= coste;
				first += coste;

				if (dist[u.first][u.second] + coste < dist[first][second]) {

					dist[first][second] = dist[u.first][u.second] + coste;


					pq.push({dist[first][second], {first, second}});

				}

				second += coste;
				first -= coste;

			}

			if (third < c) {

				int coste = min(c - third, second);

				second -= coste;
				third += coste;

				if (dist[u.first][u.second] + coste < dist[first][second]) {

					dist[first][second] = dist[u.first][u.second] + coste;



					pq.push({dist[first][second], {first, second}});

				}

				second += coste;
				third -= coste;

			}

		}

		if (third > 0) {

			if (first < a) {

				int coste = min(a - first, third);

				third -= coste;
				first += coste;

				if (dist[u.first][u.second] + coste < dist[first][second]) {

					dist[first][second] = dist[u.first][u.second] + coste;


					pq.push({dist[first][second], {first, second}});

				}

				third += coste;
				first -= coste;

			}

			if (second < b) {

				int coste = min(b - second, third);

				third -= coste;
				second += coste;

				if (dist[u.first][u.second] + coste < dist[first][second]) {

					dist[first][second] = dist[u.first][u.second] + coste;


					pq.push({dist[first][second], {first, second}});

				}

				third += coste;
				second -= coste;

			}

		}
//
//		if (donete)
//			cout << first << ' ' << second << ' ' << third << '\n';

	}

	cout << mejorCoste << ' ' << dPrima << '\n';

}

int main() {

	int nCasos;

	cin >> nCasos;

	while (nCasos--) resuelve();

	return 0;

}
