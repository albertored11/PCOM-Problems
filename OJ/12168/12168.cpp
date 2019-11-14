#include <iostream>
#include <cstdio>
#include <climits>
#include <vector>
#include <iomanip>
#include <queue>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <string>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <unordered_map>
#include <deque>
#include <unordered_set>

using namespace std;

using ii = pair<int, int>;
using vii = vector<ii>;
using vi = vector<int>;
using vvi = vector<vi>;
using vvii = vector<vii>;
using ss = pair<string, string>;
using vss = vector<ss>;

int cats, dogs, voters, dogVoters, catVoters;
vvi adjList;
vss votes;
vi match, vis;

const int MAX_VOTERS = 500;

int aug(int l) {

	if (vis[l])
		return 0;

	vis[l] = 1;

	for (auto r : adjList[l])
		if (match[r] == -1 || aug(match[r])) {
			match[r] = l;
			return 1;
		}

	return 0;

}

void resuelve() {

    cin >> cats >> dogs >> voters;

    dogVoters = 0;
    catVoters = 0;

    adjList.assign(2 * MAX_VOTERS, vi());
    votes.assign(2 * MAX_VOTERS, ss());

    for (int i = 0; i < voters; ++i) {

    	ss vote;

    	cin >> vote.first >> vote.second;

    	if (vote.first[0] == 'D') {

            for (int j = MAX_VOTERS; j < MAX_VOTERS + catVoters; ++j) {

                if (vote.first == votes[j].second || vote.second == votes[j].first) {

                    adjList[dogVoters].push_back(j);
                    adjList[j].push_back(dogVoters);

                }

            }

            votes[dogVoters] = vote;

            ++dogVoters;

    	}
    	else {

            for (int j = 0; j < dogVoters; ++j) {

                if (vote.first == votes[j].second || vote.second == votes[j].first) {

                    adjList[MAX_VOTERS + catVoters].push_back(j);
                    adjList[j].push_back(MAX_VOTERS + catVoters);

                }

            }

            votes[MAX_VOTERS + catVoters] = vote;

            ++catVoters;

    	}

    }

	int mcbm = 0;
	match.assign(2 * MAX_VOTERS, -1);

	for (int l = 0; l < dogVoters; l++) {
		vis.assign(dogVoters, 0);
		mcbm += aug(l);
	}

	cout << voters - mcbm << '\n';

}

int main() {

    int nCasos;

    cin >> nCasos;

    while (nCasos--) resuelve();

    return 0;

}
