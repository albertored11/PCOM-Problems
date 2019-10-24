#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using vi = vector<int>;

const int MAX_VIAJES = 1002;
const int MAX_CIUDADES = 102;


int numCities, ini, numEnds, numTravels;
int coste[MAX_CIUDADES][MAX_CIUDADES];
int mat[MAX_VIAJES][MAX_CIUDADES];

int f(int i, int j) {

    int *ret = &mat[i][j];

    if (*ret != -1)
        return *ret;

    for (int k = 1; k <= numCities; ++k)
        if (k != j)
            *ret = max(*ret, f(i - 1, k) + coste[k][j]);

    return *ret;

}

bool resuelve() {

    cin >> numCities >> ini >> numEnds >> numTravels;    

    if (numCities == 0 && ini == 0 && numEnds == 0 && numTravels == 0)
        return false;

    for (int i = 1; i <= numCities; ++i)
        for (int j = 1; j <= numCities; ++j)
            cin >> coste[i][j];

    for (int i = 0; i <= MAX_VIAJES; ++i)
        for (int j = 1; j <= MAX_CIUDADES; ++j)
            mat[i][j] = -1;

    for (int j = 1; j <= numCities; ++j) {
        mat[0][j] = 0;
        mat[1][j] = coste[ini][j];
    }
    
    int ret = 0;

    for (int i = 0; i < numEnds; ++i) {

        int end;

        cin >> end;

        if (!(numCities == 2 && (abs(ini - end) + numTravels) % 2 == 1))
            ret = max(ret, f(numTravels, end));

    }    

    cout << ret << '\n';

    return true;

}

int main() {

    while (resuelve());

    return 0;

}
