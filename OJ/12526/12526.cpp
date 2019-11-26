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

const int MAXN = 26;
class Trie {

public:

    int prefixes;
    int words;
    int numChilds;
    std::vector<Trie *> child;

    Trie():prefixes(0),words(0),numChilds(0),child(MAXN, nullptr) {}
    ~Trie() {
        for (int i = 0; i < MAXN; ++i)
            delete child[i];
    }

    void add(const char *s) {
        if (*s == '\0') ++words;
        else {
            Trie * t;
            if (child[*s - 'a'] == nullptr) {
                t = child[*s - 'a'] = new Trie();
                t->prefixes = 1;
                ++numChilds;
            } else {
                t = child[*s - 'a'];
                t->prefixes++;
            }
            t->add(s+1);
        }
    }
};

void recorrido(const Trie* palabras, int numPulsaciones, int &numPulsacionesTotal) {

    if (palabras->words > 0)
        numPulsacionesTotal += numPulsaciones;

    if ((palabras->numChilds > 1) || (palabras->words > 0)) {
        for (int i = 0; i < MAXN; ++i)
            if (palabras->child[i] != nullptr)
                recorrido(palabras->child[i], numPulsaciones + 1, numPulsacionesTotal);
    }
    else if (palabras->numChilds > 0) {
        for (int i = 0; i < MAXN; ++i)
            if (palabras->child[i] != nullptr)
                recorrido(palabras->child[i], numPulsaciones, numPulsacionesTotal);
    }

}

bool resuelve() {

    int numPalabras;

    cin >> numPalabras;

    if (!cin)
        return false;

    Trie palabras;
    int numPulsacionesTotal = 0;

    for (int i = 0; i < numPalabras; ++i) {

        string palabra;

        cin >> palabra;

        palabras.add(palabra.c_str());

    }

    if (palabras.numChilds == 1)
        recorrido(&palabras, 1, numPulsacionesTotal);
    else
        recorrido(&palabras, 0, numPulsacionesTotal);

    // round(x1/x2 * 100) / 100

    cout << fixed << setprecision(2) << round((float)numPulsacionesTotal / numPalabras * 100) / 100 << '\n';

    return true;

}

int main() {

    while (resuelve());
    
    return 0;
    
}    
