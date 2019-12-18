// Autores: Gonzalo Agudo Florián, Alberto Redondo Gil

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
using vvii = vector<vii>;
using si = stack<int>;

bool primerCaso;
const int INF = 10e6;

// Devuelve el número de línea al que pertenece una estación.
int linea(int estacion, const vi &primeraEstacionLinea, int numLineas) {

    int ret = 0;

    while (ret < numLineas - 1 && primeraEstacionLinea[ret + 1] <= estacion)
        ++ret;

    return ret;

}

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

bool resuelve() {

    int numLineas;
    int numCorrespondencias;
    int numConsultas;
    vi primeraEstacionLinea;
    vvii adjList;
    vi dist;
    vi parent;
    si camino;
    
    // Leer número de líneas.
    cin >> numLineas;

    // Si se lee un 0, terminar la ejecución.
    if (numLineas == 0)
        return false;
    
    if (!primerCaso)
        cout << '\n';
    else
        primerCaso = false;

    int estacion = 0;

    // Leer tiempos de trayecto entre estaciones para cada línea.
    for (int i = 0; i < numLineas; ++i) {

        int tiempo;
        bool primeraEstacion = true;

        // Guardar primera estación de la línea.
        primeraEstacionLinea.push_back(estacion);

        cin >> tiempo;

        // Seguir leyendo tiempos hasta que leamos un 0 (centinela).
        while (tiempo != 0) {

            /*
             * Si no es la primera estación, estará en la lista de adyacentes:
             * añadir una arista de coste tiempo a la siguiente estación.
             */
            if (!primeraEstacion)
                adjList[estacion].push_back({tiempo, estacion + 1});
            /*
             * Si es la primera estación, no estará en la lista de adyacentes:
             * crearla, con una arista de coste tiempo a la siguiente estación,
             * e insertarla.
             */
            else {

                vii adjEstacion0;

                adjEstacion0.push_back({tiempo, estacion + 1});
                adjList.push_back(adjEstacion0);

                primeraEstacion = false;

            }

            vii adjEstacion;

            /*
             * Crear la estación siguiente, con una arista de coste tiempo a la
             * estación actual, e insertarla en la lista de adyacentes.
             */
            adjEstacion.push_back({tiempo, estacion});
            adjList.push_back(adjEstacion);

            // Incrementar número de estaciones.
            ++estacion;

            // Leer siguiente tiempo.
            cin >> tiempo;

        }

        /*
         * Incrementar el número de estaciones para que no se solapen las
         * líneas.
         */
        ++estacion;

    }

    // Leer número de correspondencias.
    cin >> numCorrespondencias;

    // Leer correspondencias.
    for (int i = 0; i < numCorrespondencias; ++i) {

        vi correspondencia;
        // Número de líneas que pasan por la estación.
        int numLineasCorr = 0;

        /*
         * Leer la estación de cada línea en la que se da la correspondencia
         * (-1 si no hay correspondencia en esa línea; máximo 4 líneas).
         */
        for (int j = 0; j < numLineas; ++j) {

            int est;

            cin >> est;

            correspondencia.push_back(est);

            if (est != -1)
                ++numLineasCorr;

        }

        // Número de transbordos entre líneas.
        int numTransbordos = numAristas(numLineasCorr);

        // Leer tiempos de transbordo.
        for (int j = 0; j < numTransbordos; ++j) {

            int lineaA, lineaB, tiempo;
            int estacionA, estacionB;

            cin >> lineaA >> lineaB >> tiempo;

            // Calcular posiciones de cada estación en la lista de adyacentes.
            estacionA = primeraEstacionLinea[lineaA] + correspondencia[lineaA];
            estacionB = primeraEstacionLinea[lineaB] + correspondencia[lineaB];

            // Añadir aristas a la lista de adyacentes.
            adjList[estacionA].push_back({tiempo, estacionB});
            adjList[estacionB].push_back({tiempo, estacionA});

        }

    }

    cin >> numConsultas;

    // Leer consultas.
    for (int i = 0; i < numConsultas; ++i) {

        int origenLinea, origenEstacion;
        int destinoLinea, destinoEstacion;
        int origen, destino;

        cin >> origenLinea >> origenEstacion;
        cin >> destinoLinea >> destinoEstacion;

        // Calcular posiciones de cada estación en la lista de adyacentes.
        origen = primeraEstacionLinea[origenLinea] + origenEstacion;
        destino = primeraEstacionLinea[destinoLinea] + destinoEstacion;

        // Aplicar el algoritmo de Dijkstra.
        priority_queue<ii, vii, greater<ii>> pq;

        dist.assign(adjList.size(), INF);
        parent.assign(adjList.size(), -1);
        dist[origen] = 0;
        pq.push({0, origen});

        while (!pq.empty()) {

            ii front = pq.top();
            pq.pop();

            int d = front.first;
            int u = front.second;

            if (d > dist[u])
                continue;

            for (auto a : adjList[u]) {
                if (dist[u] + a.first < dist[a.second]) {
                    dist[a.second] = dist[u] + a.first;
                    parent[a.second] = u;
                    pq.push({dist[a.second], a.second});
                }
            }

        }

        if (dist[destino] == INF)
            cout << "Haberte levantado antes, Antonio.\n";
        else {

            // Ir metiendo en la pila las estaciones del camino.
            camino.push(destino);

            int pred = parent[destino];

            while (pred != -1) {
                camino.push(pred);
                pred = parent[pred];
            }

            // Número de estaciones que se llevan recorridas por la línea actual.
            int contEstacionesLinea = 1;

            // Calcular línea actual.
            int lineaActual = linea(camino.top(), primeraEstacionLinea, numLineas);

            cout << "L" << lineaActual;
            camino.pop();

            while (!camino.empty()) {

                // Calcular línea de la siguiente estación.
                int nuevaLinea = linea(camino.top(), primeraEstacionLinea, numLineas);

                /*
                 * Si se sigue en la misma línea, incrementar el número de
                 * estaciones recorridas de esa línea.
                 */
                if (nuevaLinea == lineaActual)
                    ++contEstacionesLinea;
                    /*
                     * Si no, actualizar la línea, imprimir el número de estaciones
                     * recorridas de la línea anterio y reinicializar el contador de
                     * estaciones de la línea.
                     */
                else {
                    lineaActual = nuevaLinea;
                    cout << " (" << contEstacionesLinea << ") -> L" << lineaActual;
                    contEstacionesLinea = 1;
                }

                camino.pop();

            }

            cout << " (" << contEstacionesLinea << ")\n";

            cout << "Total: " << dist[destino] << " min\n";

        }

    }
    
    
    return true;

}

int main() {
    
    primerCaso = true;
    
    while (resuelve());

    return 0;

}
