#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

int v, c;
vi match, vis;
vvi grafo;

int aug(int l) {

	if (vis[l])
		return 0;

	vis[l] = 1;

	for (auto r : grafo[l])
		if (match[r] == -1 || aug(match[r])) {
			match[r] = l;
			return 1;
		}

	return 0;

}

bool resuelve() {

	cin >> v;

	if (!cin)
		return false;

	vector<unordered_map<char, int>> words(v);

	cin >> c;

	grafo.assign(c + v, vi());

	for (int i = 0; i < v; ++i) {

		string word;

		cin >> word;

		for (int j = 0; j < word.length(); ++j) {

			if (words[i].count(word[j]) == 0)
				words[i].emplace(word[j], 1);
			else
				++words[i].at(word[j]);

		}

	}

	for (int i = 0; i < c; ++i) {

		string challenge;
		unordered_map<char, int> chMap;
		bool vb[502];

		for (int j = 0; j < v; ++j)
			vb[j] = true;

		cin >> challenge;

		for (int j = 0; j < challenge.length(); ++j) {

			if (chMap.count(challenge[j]) == 0)
				chMap.emplace(challenge[j], 1);
			else
				++chMap.at(challenge[j]);

		}

		for (pair<char, int> ch : chMap) {

			for (int j = 0; j < words.size(); ++j) {

				if (vb[j] && words[j].count(ch.first)) {

					vb[j] = ch.second <= words[j].at(ch.first);

				}
				else
					vb[j] = false;

			}

		}

		for (int j = 0; j < v; ++j) {

			if (vb[j]) {

				grafo[j].push_back(v + i);
				grafo[v + i].push_back(j);

			}

		}

	}

	int mcbm = 0;
	match.assign(v + c, -1);

	for (int l = 0; l < v; l++) {
		vis.assign(v, 0);
		mcbm += aug(l);
	}

	cout << mcbm << '\n';

	return true;

}

int main() {

	while (resuelve());

}
