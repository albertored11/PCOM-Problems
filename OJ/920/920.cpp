#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

using T = double;

struct pt {

    T x, y;

    pt operator+(pt p) const {
        return { x + p.x, y + p.y };
    }

    pt operator-(pt p) const {
        return { x - p.x, y - p.y };
    }

    pt operator*(T d) const { return {x*d, y*d}; }
    pt operator/(T d) const { return {x/d, y/d}; } // only for floating-point
    bool operator==(pt o) const { return x == o.x && y == o.y; }
    bool operator!=(pt o) const { return !(*this == o); }
    bool operator<(pt o) const { // sort points lexicographically
        if (x == o.x) return y < o.y;
        return x < o.x;
    }

/*    bool operator<(pt o) const { // #define EPS 1e-9

        if (fabs(x - o.x) < EPS) return y < o.y;

        return x < o.x;

    }*/

};

T sq(pt v) {

    return v.x * v.x + v.y * v.y;

}

double abs(pt v) {

    return sqrt(sq(v));

}

// Euclidean distance
double dist(pt a, pt b) {

    return hypot(a.x - b.x, a.y - b.y);

}

T cross(pt v, pt w) {

    return v.x * w.y - v.y * w.x;

}

pt perp(pt p) {

    return { -p.y, p.x };

}

struct line {

    pt v;
    T c;

    // from direction vector v and offset c
    line(pt v, T c) : v(v), c(c) {}

    // from equation ax + by = c
    line(T a, T b, T c) : v({b, -a}), c(c) {}

    // from points p and q
    line(pt p, pt q) : v(q - p), c(cross(v, p)) {}

    T side(pt p) {

        return cross(v, p) - c;

    }

    double dist(pt p) {

        return abs(side(p)) / abs(v);

    }

    pt proj(pt p) {

        return p - perp(v) * side(p) / sq(v);

    }

};

bool inter(line l1, line l2, pt &out) {

    T d = cross(l1.v, l2.v);

    if (d == 0)
        return false;

    out = (l2.v * l1.c - l1.v * l2.c) / d;

    return true;

}

void resuelve() {

    int numPuntos;
    vector<pt> puntos;
    double res = 0;
    int alturaMaxima = 0;

    cin >> numPuntos;

    for (int i = 0; i < numPuntos; ++i) {

        pt punto;

        cin >> punto.x >> punto.y;

        puntos.push_back(punto);

    }

    sort(puntos.begin(), puntos.end());

    for (int i = puntos.size() - 2; i >= 0; i -= 1) {

        line sol(0, 1, alturaMaxima);

        pt punto = puntos[i];
        pt puntoAnt = puntos[i + 1];

        if (punto.y > alturaMaxima) {

            line linea(punto, puntoAnt);
            pt corte;

            inter(linea, sol, corte);

            res += dist(punto, corte);

            alturaMaxima = punto.y;

        }

    }

    cout << fixed << setprecision(2) << res << '\n';

}

int main() {

    int nCasos;

    cin >> nCasos;

    while (nCasos--) resuelve();

    return 0;

}
