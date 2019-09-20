#include <iostream>
#include <map>

using namespace std;

bool resuelve() {

	int numHeads, numKnights;

	cin >> numHeads >> numKnights;

	if (numHeads == 0 && numKnights == 0)
		return false;
	
	map<int, int> heads, knights;

	for (int i = 0; i < numHeads; ++i) {

		int head;

		cin >> head;

		if (heads.count(head) == 1)
			++heads[head];
		else
			heads.emplace(head, 1);

	}

	for (int i = 0; i < numKnights; ++i) {

		int knight;

		cin >> knight;

		if (knights.count(knight) == 1)
			++knights[knight];
		else
			knights.emplace(knight, 1);

	}

	if (numKnights < numHeads)
		cout << "Loowater is doomed!\n";
	else {

		int price = 0;

		while (!heads.empty()) {

			map<int, int>::iterator firstHead = heads.begin();
			map<int, int>::iterator firstKnight = knights.lower_bound(firstHead->first);

			if (firstKnight == knights.end())
				break;

			price += firstKnight->first;

			--firstHead->second;

			if (firstHead->second == 0)
				heads.erase(firstHead);

			--firstKnight->second;

			if (firstKnight->second == 0)
				knights.erase(firstKnight);

		}

		if (heads.empty())
			cout << price << '\n';
		else
			cout << "Loowater is doomed!\n";

	}

	return true;

}

int main() {

	while (resuelve());

	return 0;

}
