#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int df[] = {1, 0, -1, 0}, dc[] = {0, 1, 0, -1};

typedef struct {

	int tam;
	char c;

} tPot;

bool operator<(tPot a, tPot b) {

	if(a.tam == b.tam)
		return a.c < b.c;

	return a.tam > b.tam;
}

bool operator>(tPot a, tPot b) {

	if(a.tam == b.tam)
		return a.c > b.c;

	return a.tam < b.tam;
}

bool operator==(tPot a, tPot b) {

	return a.tam == b.tam && a.c == b.c;

}

int f, c, problem = 1;


bool ok(int i, int j) {
	return 0 <= i && i < f && 0 <= j && j < c;
}

int dfs (int i, int j, char map[50][50], bool visited[50][50]) {

	int tam = 1; visited[i][j] = true;
	for(int k = 0; k < 4; ++k) {

		int ni = i + df[k], nj = j + dc[k];
		if(ok(ni, nj) && map[ni][nj] == map[i][j] && !visited[ni][nj])
			tam += dfs(ni, nj, map, visited);
	}
	return tam;
}

bool resuelve() {

	cin >> f >> c;

	if (f == 0 && c == 0)
		return false;

	char map[50][50];
	bool visited[50][50];
	vector<tPot> pots;


	for (int i = 0; i < f; ++i) {
		for (int j = 0; j < c; ++j) {
			cin >> map[i][j];
			if (map[i][j] != '.') visited[i][j] = false;
			else visited[i][j] = true;
		}
	}

	for (int i = 0; i < f; ++i) {
		for(int j = 0; j < c; ++j) {
			if(!visited [i][j]) {
				tPot pot;
				pot.tam = dfs(i, j, map, visited);
				pot.c = map[i][j];
				pots.push_back(pot);
			}
		}
	}

	sort(pots.begin(), pots.end());

	cout << "Problem " << problem << ":\n";

	for (auto a : pots)
		cout << a.c << ' ' << a.tam << '\n';


	return true;
}


int main() {

	while(resuelve()) ++problem;


	return 0;

}
