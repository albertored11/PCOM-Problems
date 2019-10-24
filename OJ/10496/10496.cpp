#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

using ii = pair<int,int>;
using vii = vector<ii>;
using vi = vector<int>;

const int INF = 10e6;
const int MAX_BEEP_BIN = 1024;
const int MAX_CAS = 11;

int nCasos;
int X, Y, nBeep;
ii ini;
vii beepers;
vi dist;
int mat[MAX_BEEP_BIN][MAX_CAS];

bool contiene(ii a) {
    int i = 0;

    while(i < beepers.size() && beepers[i] != a)
        ++i;

    return i < beepers.size();
}


int manhattan(ii a, ii b) {

    return abs(a.first - b.first) + abs(a.second + b.second);

}

int f(int i, int j) {

    int *ret = &mat[i][j];

    if (*ret != INF)
        return *ret;

    int beepBin = i;

    if (beepBin == 0)
        *ret = manhattan(ini, beepers[j]);
    else {

        for (int k = 0; k < beepers.size(); ++k) {

            if (beepBin % 2 == 1)
                *ret = min(*ret, f(i - (1 << k), k) + manhattan(beepers[i], beepers[k]));

            beepBin /= 2;

        }

    }

    return *ret;

}

void resuelve() {    

    cin >> X >> Y;

    cin >> ini.first >> ini.second >> nBeep;

    beepers.clear();    

    for (int i = 0; i < MAX_BEEP_BIN; ++i)
        for (int j = 0; j < MAX_CAS; ++j)
            mat[i][j] = INF;

    for (int i = 0; i < nBeep; ++i) {

        ii beep;
        cin >> beep.first >> beep.second;
        if (!contiene(beep))
            beepers.push_back(beep);

        mat[(1 << i)][i] = manhattan(ini, beep);

    }

    dist.assign(beepers.size(), INF);

    cout << "The shortest path has length " << f((1 << beepers.size()) - 1, beepers.size()) << '\n';    

}


int main() {    

    cin >> nCasos;

    while(nCasos--)resuelve();


    return 0;
}