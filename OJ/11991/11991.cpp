#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

bool resuelve() {

	int n;

	cin >> n;

	if (!cin)
		return false;

	unordered_map<int, vector<int>> info;
	int m;

	cin >> m;

	for (int i = 0; i < n; ++i) {

		int elem;

		cin >> elem;

		if (info.count(elem) == 0) {

			vector<int> v;
			v.push_back(i + 1);
			info.insert({elem, v});

		}
		else {

			unordered_map<int, vector<int>>::iterator iter = info.find(elem);
			iter->second.push_back(i + 1);

		}

	}

	for (int i = 0; i < m; ++i) {

		int k, v;

		cin >> k >> v;

		if (info.count(v) == 0)
			cout << 0;
		else {

			unordered_map<int, vector<int>>::iterator iter = info.find(v);

			if (iter->second.size() < k)
				cout << 0;
			else
				cout << iter->second[k - 1];

		}

		cout << '\n';

	}

	return true;

}

int main() {

	while (resuelve());

	return 0;

}
