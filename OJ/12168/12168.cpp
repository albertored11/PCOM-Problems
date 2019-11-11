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

int cats, dogs, voters, dogVoters;
vvi adjList;
vss votes;
vi match, vis;

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

    adjList.assign(voters, vi());
    votes.clear();

    for (int i = 0; i < voters; ++i) {

    	ss vote;

    	cin >> vote.first >> vote.second;

    	if (vote.first[0] == 'D')
			++dogVoters;

    	for (int j = 0; j < votes.size(); ++j) {

    		if (vote.first == votes[j].second || vote.second == votes[j].first) {

    			adjList[i].push_back(j);
				adjList[j].push_back(i);

    		}

    	}

    	votes.push_back(vote);

    }

	int mcbm = 0;
	match.assign(voters, -1);

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
