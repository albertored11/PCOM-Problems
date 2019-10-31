#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using vi = vector<int>;

bool resuelve() {

	int encuentros;

	cin >> encuentros;

	if (!cin)
		return false;

	int golesComprar;
	int res = 0;
	int numEmpatados = 0;
	vi diferencias;

	cin >> golesComprar;

	for (int i = 0; i < encuentros; ++i) {

		int tu, otro;

		cin >> tu >> otro;

		if (tu > otro)
			res += 3;
		else if (tu == otro) {
			++numEmpatados;
			++res;
		}
		else {
			diferencias.push_back(otro - tu);
		}

	}

	sort(diferencias.begin(), diferencias.end());

	while (numEmpatados > 0 && golesComprar > 0) {
		--numEmpatados;
		--golesComprar;
		res += 2;
	}

	for (int dif : diferencias) {

		if (golesComprar < dif)
			break;
		

		if (golesComprar > dif) {
			golesComprar -= (dif + 1);
			res += 3;
		}
		else {
			golesComprar -= dif;
			++res;
		}

	}

	cout << res << '\n';

	return true;

}

int main() {

	while (resuelve());

}
