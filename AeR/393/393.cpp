#include <iostream>
#include <cstdio>
#include <climits>
#include <vector>
#include <iomanip>
#include <queue> // Cola de mayor a menor por defecto en priority
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
using vvi = vector<vi>; // para listas de adyacencia
using vs = vector<string>;

const int MAX_TAM = 300;

typedef bool tSopa[MAX_TAM][MAX_TAM];

std::string T,P;
std::vector<int> b; // back table
int n, m;
// n = length of T, m = length of P
void kmpPreprocess() { // before calling kmpSearch
    int i = 0, j = -1; b[0] = -1;
    while (i < m) {
        while (j >= 0 && P[i] != P[j]) j = b[j];
        ++i; ++j;
        b[i] = j;
    }
}

void kmpSearch() {
    int i = 0, j = 0;
    while (i < n) {
        while (j >= 0 && T[i] != P[j])
            j = b[j]; // different reset j using b
        ++i; ++j;
        // same, advance both pointers
        if (j == m) {
            printf("P is found at index %d in T\n",i-j);
            j = b[j];
        }
    }
}


bool resuelve() {

    int c;

    cin >> c;

    if (!cin)
        return false;

    int f;
    tSopa sopa;
    int numPatrones;
    vs patrones;
    unordered_map<string, int> result;

    cin >> f;

    for (int i = 0; i < f; ++i) {

        for (int j = 0; j < c; ++j) {

            char digito;

            cin >> digito;

            sopa[i][j] = digito - '0';

        }

    }

    cin >> numPatrones;

    for (int i = 0; i < numPatrones; ++i) {

        string patron;

        cin >> patron;

        patrones.push_back(patron);

    }

    return true;

}

int main() {

    while (resuelve());
    
    return 0;
    
}    
