#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

using T = double;

int w_desp[] = { -1, -1, 1, 1 };
int h_desp[] = { 1, -1, 1, -1 };

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

T cross(pt v, pt w) {

    return v.x * w.y - v.y * w.x;

}

T orient(pt a, pt b, pt c) {

    return cross(b - a, c - a);

}

pt translate(pt v, pt p) {

    return p + v;

}

// rotate p by a certain angle a counter-clockwise around origin
pt rotate(pt p, double a) {

    return {p.x * cos(a) - p.y * sin(a), p.x * sin(a) + p.y * cos(a)};

}

double areaPolygon(vector<pt> const& p) {

    double area = 0.0;

    for (int i = 0; i < int(p.size()) - 1; ++i)
        area += cross(p[i], p[i + 1]);

    return abs(area) / 2.0;

}

// devuelve true si r está en el lado izquierdo de la línea pq
bool ccw(pt p, pt q, pt r) {
    return orient(p, q, r) > 0; // >= para puntos colineales
}
// devuelve un polígono con la envolvente convexa de la nube de puntos P
vector<pt> convexHull(vector<pt> & P) {
    int n = int(P.size()), k = 0;
    vector<pt> H(2*n);
    sort(P.begin(), P.end());
// build lower hull
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && !ccw(H[k-2], H[k-1], P[i])) --k;
        H[k++] = P[i];
    }
// build upper hull
    for (int i = n-2, t = k+1; i >= 0; --i) {
        while (k >= t && !ccw(H[k-2], H[k-1], P[i])) --k;
        H[k++] = P[i];
    }
    H.resize(k);
    return H;
}

void resuelve() {

    int numBoards;
    double areaBoards = 0;
    double areaMould;
    vector<pt> puntos;
    vector<pt> mould;

    cin >> numBoards;

    for (int i = 0; i < numBoards; ++i) {

        pt centro;
        double w, h, phi;

        cin >> centro.x >> centro.y >> w >> h >> phi;

        // pasar phi de grados a radianes y cambiarle el signo
        phi *= -M_PI;
        phi /= 180;

        for (int j = 0; j < 4; ++j) {

            pt punto = {(w / 2) * w_desp[j], (h / 2) * h_desp[j]};

            punto = rotate(punto, phi);
            punto = translate(punto, centro);

            puntos.push_back(punto);

        }

        areaBoards += w * h;

    }

    mould = convexHull(puntos);

    areaMould = areaPolygon(mould);

    cout << fixed << setprecision(1) << 100 * areaBoards / areaMould << " %\n";

}

int main() {

    int nCasos;

    cin >> nCasos;

    while (nCasos--) resuelve();

    return 0;

}
