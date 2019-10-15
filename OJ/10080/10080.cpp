#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

using dd = pair<double, double>;
using vdd = vector<dd>;
using vb = vector<bool>;
using vi = vector<int>;
using vvi = vector<vi>;

vi match;
vb vis;

double distancia(dd a, dd b) {

	return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));

}

int aug(int l, vvi adjList) {

	if (vis[l])
		return 0;

	vis[l] = 1;

	for (auto r : adjList[l])
		if (match[r] == -1 || aug(match[r], adjList)) {
			match[r] = l;
			return 1;
		}

	return 0;

}

bool resuelve() {

	int castores;

	cin >> castores;

	if (!cin)
		return false;

	int madrig, tiempo, vel;
	double distanciaMax;
	vdd listCastores;
	vdd listMadrig;
	vvi adjList(castores);

	cin >> madrig >> tiempo >> vel;

	for (int i = 0; i < castores; ++i) {

		dd castor;

		cin >> castor.first >> castor.second;

		listCastores.push_back(castor);

	}

	for (int i = 0; i < madrig; ++i) {

		dd mad;

		cin >> mad.first >> mad.second;

		listMadrig.push_back(mad);

	}

	distanciaMax = tiempo * vel;

	for (int i = 0; i < castores; ++i)
		for (int j = 0; j < madrig; ++j)
			if (distancia(listCastores[i], listMadrig[j]) <= distanciaMax)
				adjList[i].push_back(j);

	int numSinPareja = castores;
	match.assign(castores + madrig, -1);

	for (int l = 0; l < castores; ++l) {
		vis.assign(castores, false);
		numSinPareja -= aug(l, adjList);
	}

	cout << numSinPareja << '\n';

	return true;

}

int main() {

	while (resuelve());

	return 0;

}
