#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>

using namespace std;

const int NUM_CASOS = 100;
const int MAX_LINEAS = 50;
const int MAX_ESTACIONES = 100;
const int MAX_TIEMPO = 10;
const int MAX_CORRESPONDENCIAS = MAX_LINEAS;
const int MAX_EST_CORR = 4;
const int MAX_CONSULTAS = 20;

vector<vector<bool>> estacionesCorr;

bool contiene(vector<int> &v, int elem) {

    for (int e : v)
        if (e == elem)
            return true;

    return false;

}

void generarCaso(ofstream &f) {

    int L = rand() % (MAX_LINEAS - 1) + 1;

    estacionesCorr.assign(L, vector<bool>());

    f << L << '\n';

    for (int i = 0; i < L; ++i) {

        int E = rand() % (MAX_ESTACIONES - 1) + 1;

        for (int j = 0; j < E; ++j) {
            f << rand() % (MAX_TIEMPO - 1) + 1 << ' ';
            estacionesCorr[i].push_back(false);
        }

        f << 0 << '\n';

    }

    if (L > 1) {

        int C = rand() % MAX_CORRESPONDENCIAS;

        f << C << '\n';

        for (int i = 0; i < C; ++i) {

            vector<int> correspondencias;
            vector<int> lineas;
            int numLineas = min(rand() % (MAX_EST_CORR - 1) + 2, L);

            correspondencias.assign(L, -1);

            for (int j = 0; j < numLineas; ++j) {

                int linea;

                do {
                    linea = rand() % L;
                } while (contiene(lineas, linea));

                int lineaAnterior = (linea - 1 + L) % L;

                do {

                    int estacion = rand() % estacionesCorr[linea].size();
                    int estacionAnterior = (estacion - 1 + estacionesCorr[linea].size()) % estacionesCorr[linea].size();

                    while (estacionesCorr[linea][estacion] && estacion != estacionAnterior) {
                        ++estacion;
                        estacion %= estacionesCorr[linea].size();
                    }

                    if (estacion == estacionAnterior) {
                        linea++;
                        linea %= L;
                    }
                    else {
                        correspondencias[linea] = estacion;
                        estacionesCorr[linea][estacion] = true;
                        break;
                    }

                } while (linea != lineaAnterior);

                lineas.push_back(linea);

                if (linea == lineaAnterior) {
                    cout << "ERROR. Prueba con otros valores para las constantes.\n";
                    break;
                }

            }

            for (int j = 0; j < correspondencias.size(); ++j) {

                f << correspondencias[j];

                if (j < correspondencias.size() - 1)
                    f << ' ';

            }

            f << '\n';

            for (int j = 0; j < lineas.size(); ++j)
                for (int k = j + 1; k < lineas.size(); ++k)
                    f << lineas[j] << ' ' << lineas[k] << ' ' << rand() % MAX_TIEMPO << '\n';

        }

    }
    else
        f << 0 << '\n';

    int Q = rand() % MAX_CONSULTAS;

    f << Q << '\n';

    for (int i = 0; i < Q; ++i) {

        int linea = rand() % L;

        f << linea << ' ' << rand() % estacionesCorr[linea].size() << ' ';

        linea = rand() % L;

        f << linea << ' ' << rand() % estacionesCorr[linea].size() << '\n';

    }

}

int main() {

    srand(time(nullptr));

    ofstream f;

    f.open("sample.in");

    for (int i = 0; i < NUM_CASOS; ++i)
        generarCaso(f);

    f << 0 << '\n';

    f.close();

    return 0;

}
