// Autores: Gonzalo Agudo Florián, Alberto Redondo Gil

#include <fstream>
#include <cstdlib>
//#include <ctime>
#include <vector>
#include <iostream>
#include <unordered_set>

using namespace std;

const int NUM_CASOS = 100;
const int MAX_LINEAS = 15;
const int MAX_ESTACIONES = 30;
const int MAX_TIEMPO = 15;
const int MAX_CORRESPONDENCIAS = MAX_LINEAS;
const int MAX_EST_CORR = 4;
const int MAX_CONSULTAS = 5;

/*
 * Devuelve el número de transbordos que hay en función del número de líneas que
 * coinciden en una estación.
 */
int numAristas(int numLineas) {
    
    if (numLineas == 2)
        return 1;
    
    if (numLineas == 3)
        return 3;
    
    return 6;
    
}

// Dado un string con espacios y enteros, parsea los enteros a un vector.
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

// Comprueba que el caso cumple las restricciones.
bool esBueno(const string &buf, int comienzoCorr) {

    // Sacar número de líneas.
    string strL = "";
    int a = 0;
    
    while (buf[a] != '\n') {
        strL += buf[a];
        ++a;
    }
    
    int L = stoi(strL);
    
    // Si solo hay una línea, no hay correspondencias y no hay posibles errores.
    if (L == 1)
        return true;
    
    // Sacar número de correspondencias.
    string strC = "";
    int it = comienzoCorr;
    
    while (buf[it] != '\n') {
        strC += buf[it];
        ++it;
    }
    
    ++it;
    
    int C = stoi(strC);
    
    // Para guardar qué estaciones de cada línea están en las correspondencias
    vector<unordered_set<int>> estaciones;
    
    estaciones.assign(L, unordered_set<int>());
    
    for (int i = 0; i < C; ++i) {
    
        // Sacar datos de la correspondencia.
        string strCorr = "";
        vector<int> corr;
        int numLineas = 0;
        
        while (buf[it] != '\n') {
            strCorr += buf[it];
            ++it;
        }
        
        ++it;
        
        corr = parseLine(strCorr);
        
        /*
         * Comprobar si las estaciones de cada línea no han sido usadas
         * anteriormente.
         */
        for (int j = 0; j < corr.size(); ++j) {
            
            if (corr[j] != -1) {
                
                if (estaciones[j].count(corr[j]))
                    return false;
                
                estaciones[j].emplace(corr[j]);
                
                ++numLineas;
                
            }
            
        }
        
        // Saltar los tiempos de transbordo.
        int numConexiones = numAristas(numLineas);
        
        for (int j = 0; j < numConexiones; ++j) {
    
            while (buf[it] != '\n')
                ++it;
            
            ++it;
            
        }
    
    }
    
    return true;

}

/*
 * Generar caso de prueba. Devuelve la posición del buffer en la que empieza la
 * parte de las correspondencias.
 */
int generarCaso(string &buf) {

    buf = "";
    
    // Generar número de líneas (no puede ser 0)
    int L = rand() % (MAX_LINEAS - 1) + 1;
    vector<int> numEstaciones;
    int comienzoCorr;

    buf += to_string(L) + '\n';

    // Generar tiempos entre estaciones para cada línea.
    for (int i = 0; i < L; ++i) {
        
        // El número de estaciones tiene que ser > 0.
        int E = rand() % (MAX_ESTACIONES - 1) + 1;

        numEstaciones.push_back(E);
    
        // Los tiempos tienen que ser > 0.
        for (int j = 0; j < E; ++j)
            buf += to_string(rand() % (MAX_TIEMPO - 1) + 1) + ' ';

        buf += "0\n";

    }
    
    // Ahora comienza la parte de las correspondencias.
    comienzoCorr = buf.size();

    // Si hay más de una línea, puede haber correspondencias.
    if (L > 1) {

        int C = rand() % MAX_CORRESPONDENCIAS;

        buf += to_string(C) + '\n';

        // Generar cada correspondencia.
        for (int i = 0; i < C; ++i) {
            
            // Número de líneas involucradas entre 2 y 4.
            int numLineas = min(rand() % (MAX_EST_CORR - 1) + 2, L);
            
            // Vector que indica si cada línea ha sido usada.
            vector<bool> lineasUsadas;
            
            lineasUsadas.assign(L, false);

            // Generar líneas.
            for (int j = 0; j < numLineas; ++j) {
                
                int linea = rand() % L;
                
                // Si la línea ha sido usada, generar otra.
                while (lineasUsadas[linea])
                    linea = rand() % L;
                
                lineasUsadas[linea] = true;

            }
            
            // Escribir datos de las líneas en el buffer.
            for (int j = 0; j < L; ++j) {
                
                if (!lineasUsadas[j])
                    buf += "-1 ";
                else {
                    
                    // Elegir una estación aleatoria entre las de esa línea.
                    int est = rand() % numEstaciones[j];
                    
                    buf += to_string(est);
                    
                    if (j < L - 1)
                        buf += ' ';
                    
                }
                
            }
            
            buf += '\n';

            // Generar tiempos de transbordo.
            for (int j = 0; j < L; ++j) {
                
                if (lineasUsadas[j]) {
    
                    for (int k = j + 1; k < L; ++k) {
                        
                        if (lineasUsadas[k]) {
                            
                            int tiempo = rand() % MAX_TIEMPO;
                            
                            buf += to_string(j) + ' ' + to_string(k) + ' ' + to_string(tiempo) + '\n';
                            
                        }
                        
                    }
    
                }
                
            }

        }

    }
    // Si solo hay una línea, no puede haber correspondencias.
    else
        buf += "0\n";

    // Generar número de consultas (no puede ser 0).
    int Q = rand() % (MAX_CONSULTAS - 1) + 1;

    buf += to_string(Q) + '\n';

    // Generar consultas.
    for (int i = 0; i < Q; ++i) {

        int linea = rand() % L;

        buf += to_string(linea) + ' ' + to_string(rand() % numEstaciones[linea]) + ' ';

        linea = rand() % L;
    
        buf += to_string(linea) + ' ' + to_string(rand() % numEstaciones[linea]) + '\n';

    }
    
    buf += '\n';
    
    return comienzoCorr;

}

int main() {

//    srand(time(nullptr));
    srand(1);

    ofstream f;
    int i = 0;

    f.open("sample.in");

    while (i < NUM_CASOS) {
        
        string buf;
        
        int comienzoCorr = generarCaso(buf);
        
        if (esBueno(buf, comienzoCorr)) {
            f << buf;
            ++i;
        }
        
    }

    f << 0 << '\n';

    f.close();

    return 0;

}
