#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>

using namespace std;

const double epsilon = 10e-7;

double busca(double x, double y, double c, double ini, double fin) {

	double b = (ini + fin) / 2;
	double cAux = (sqrt(x * x - b * b) * sqrt(y * y - b * b)) /
			(sqrt(x * x - b * b) + sqrt(y * y - b * b));

	if (abs(c - cAux) < epsilon)
		return b;
	else if (cAux < c)
		return busca(x, y, c, ini, b);
	else
		return busca(x, y, c, b, fin);

}

bool resuelve() {

	double x;

	cin >> x;

	if (!cin)
		return false;

	double y, c;

	cin >> y >> c;

	cout << fixed << setprecision(3) << busca(x, y, c, 0, min(x, y)) << '\n';

	return true;

}

int main() {

	while (resuelve());

	return 0;

}
