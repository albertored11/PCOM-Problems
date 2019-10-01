#include <iostream>
#include <vector>
#include <cstring>
#include <iomanip>
#include <unordered_map>

using namespace std;

const int MAX = 110;
const int INF = 10000;

int caso = 1;

bool resuelve() {

	int a, b;

	cin >> a >> b;

	if (a == 0 && b == 0)
		return false;

	int adjMat[MAX][MAX];
	unordered_map<int, int> rename;

	memset(adjMat, INF, sizeof(int) * MAX * MAX);

	while (a != 0 || b != 0) {

		if (rename.count(a) == 0)
			rename.emplace(a, rename.size());

		if (rename.count(b) == 0)
			rename.emplace(b, rename.size());

		adjMat[rename.at(a)][rename.at(b)] = 1;

		cin >> a >> b;

	}

	double clicks = 0;
	int numCaminos = rename.size() * (rename.size() - 1);

	for (int k = 0; k < rename.size(); ++k)
		for (int i = 0; i < rename.size(); ++i)
			for (int j = 0; j < rename.size(); ++j)
				if (i != j && adjMat[i][k] + adjMat[k][j] < adjMat[i][j])
					adjMat[i][j] = adjMat[i][k] + adjMat[k][j];

	for (int i = 0; i < rename.size(); ++i)
		for (int j =  0; j < rename.size(); ++j)
			if (i != j && adjMat[i][j] < INF)
				clicks += adjMat[i][j];

	cout << "Case " << caso << ": average length between pages = " << fixed << setprecision(3) << clicks / numCaminos << " clicks\n";

	return true;

}

int main() {

	while (resuelve()) ++caso;

	return 0;

}
