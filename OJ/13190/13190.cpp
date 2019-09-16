#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
using namespace std;

typedef struct{
	string nombre;
	int time;
	int frequency;
	int order;
} tMed;

bool operator==(tMed a, tMed b){

	return a.time == b.time && a.order == b.order;

}

bool operator<(tMed a, tMed b){

	if (a.time == b.time)
		return a.order > b.order;
	else
		return a.time > b.time;

}

void resuelve() {

	int n, k;
	cin >> n >> k;

	priority_queue<tMed> cola;
	for(int i = 0;i < n; ++i) {
		tMed antonio;
		cin >> antonio.nombre >> antonio.time;
		antonio.frequency = antonio.time;
		antonio.order = i;
		cola.push(antonio);
	}

	while(k--){

		tMed antonio = cola.top();

		cout << antonio.time << ' ' << antonio.nombre << '\n';

		cola.pop();

		antonio.time += antonio.frequency;

		cola.push(antonio);



	}




}

int main() {

	int n;
	cin >> n;

	while(n--) {
		(resuelve());
	}

	return 0;

}
