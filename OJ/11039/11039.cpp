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

void resuelve() {

    int numFloors;
    vi negativeFloors;
    vi positiveFloors;
    int lastNum;
    int size = 0;
    bool positive;
    int iPos = 0, iNeg = 0;

    cin >> numFloors;

    for (int i = 0; i < numFloors; ++i) {

        int floor;

        cin >> floor;

        if (floor < 0)
            negativeFloors.push_back(abs(floor));
        else
            positiveFloors.push_back(floor);

    }

    sort(negativeFloors.begin(), negativeFloors.end());
    sort(positiveFloors.begin(), positiveFloors.end());

    if (negativeFloors.empty() && positiveFloors.empty()) {
        cout << 0 << '\n';
        return;
    }

    if (negativeFloors.empty() || positiveFloors.empty()) {
        cout << 1 << '\n';
        return;
    }

    if (negativeFloors[0] < positiveFloors[0]) {
        lastNum = negativeFloors[0];
        positive = true;
        ++iNeg;
    }
    else {
        lastNum = positiveFloors[0];
        positive = false;
        ++iPos;
    }

    ++size;

    while (iNeg < negativeFloors.size() || iPos < positiveFloors.size()) {

        if (positive) {

            while (iPos < positiveFloors.size() && positiveFloors[iPos] <= lastNum)
                ++iPos;

            if (iPos == positiveFloors.size())
                break;

            ++size;
            lastNum = positiveFloors[iPos];

        }
        else {

            while (iNeg < negativeFloors.size() && negativeFloors[iNeg] <= lastNum)
                ++iNeg;

            if (iNeg == negativeFloors.size())
                break;

            ++size;
            lastNum = negativeFloors[iNeg];

        }

        positive = !positive;

    }

    cout << size << '\n';

}

int main() {

    int nCasos;

    cin >> nCasos;

    while (nCasos--) resuelve();
    
    return 0;
    
}    
