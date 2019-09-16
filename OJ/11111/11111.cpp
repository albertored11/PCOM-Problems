#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <unordered_set>
using namespace std;

vector<int> parseLine(string line) {

	vector<int> ret;
	string aux;
	int i = 0;

	while (i < line.length()) {

		aux = "";

		while (i < line.length() && line[i] != ' ') {
			aux += line[i];
			++i;
		}

		if (aux != "")
			ret.push_back(stoi(aux));

		++i;

	}

	return ret;

}

bool matCorrecta(vector<int> mat, int ini, int fin, int tam) {

	if (ini >= fin && tam > 0)
		return true;

	if (mat[ini] >= 0)
		return false;

	/*if ((mat[ini + 1] < 0 || fin == ini + 1) && mat[ini] + mat[fin] == 0) {
		if (mat[fin] >= tam) return false;
		else return matCorrecta(mat, ini + 1, fin - 1, mat[fin]);
	}*/

	if (mat[ini + 1] > 0) {
		if (mat[ini] + mat[ini + 1] != 0)
			return false;
		return matCorrecta(mat, ini + 2, fin, tam - mat[ini + 1]);
	}

	int i = ini + 1;

	while (mat[ini] + mat[i] != 0  && i <= fin)
		++i;

	if (i > fin)
		return false;

	if (i == fin && (mat[ini + 1] < 0 || fin == ini + 1) && mat[ini] + mat[fin] == 0) {
		if (mat[fin] >= tam) return false;
		else return matCorrecta(mat, ini + 1, fin - 1, mat[fin]);
	}

	return matCorrecta(mat, ini, i, tam) && matCorrecta(mat, i + 1, fin, tam - mat[i]);

}

bool resuelve() {

	string line;

	getline(cin, line);

	if (!cin)
		return false;

	vector<int> mat = parseLine(line);

	int tam;

	if (mat.size() == 0 || (mat.size() % 2 == 0 && mat[0] < 0 && mat[0] + mat[mat.size() - 1] == 0 && (matCorrecta(mat, 1, mat.size() - 2, mat[mat.size() - 1]))))
		cout << ":-) Matrioshka!\n";
	else
		cout << ":-( Try again.\n";

	return true;
}

int main() {

	while (resuelve());

	return 0;

}
