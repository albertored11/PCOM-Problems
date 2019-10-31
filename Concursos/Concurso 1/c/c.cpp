#include <iostream>

using namespace std;

bool resuelve() {

	int h1, m1, h2, m2;

	cin >> h1 >> m1 >> h2 >> m2;

	if (h1 == 0 && m1 == 0 && h2 == 0 && m2 == 0)
		return false;

	int res = 0;

	/*
	if (h2 < h1)
		res += (24 - h1 + h2) * 60 + m2 - m1;
	else if (h2 > h1)
		res += (h2 - h1) * 60 + m2 - m1;
	else if (m2 > m1)
		res += m2 - m1;
	else
		res += 60 * 24 - (m1 - m2);		
	*/

	res = ((h2 * 60 + m2) - (h1 * 60 + m1) + 60 * 24) % (60 * 24);

	cout << res << '\n';

	return true;

}

int main() {

	while (resuelve());

}
