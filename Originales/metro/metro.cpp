#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using vi = vector<int>;
using ii = pair<int, int>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 10e6;

int numAristas(int numLineas) {

    if (numLineas == 2)
        return 1;

    if (numLineas == 3)
        return 3;

    return 6;

}

// TODO separar la definición de las consultas.
bool resuelve() {

    int numLineas;
    int numCorrespondencias;
    int numConsultas;
    vi primeraEstacionLinea;
    vvii adjList;
    vi dist;

    // Leer número de líneas.
    cin >> numLineas;

    // Si se lee un 0, terminar la ejecución.
    if (numLineas == 0)
        return false;

    int estacion = 0;

    // Leer tiempos de trayecto entre estaciones para cada línea.
    for (int i = 0; i < numLineas; ++i) {

        // TODO hacerlo sin la variable estacion.

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
                    pq.push({dist[a.second], a.second});
                }
            }

        }

        cout << "El tiempo total de trayecto es de " << dist[destino] << " minutos.\n";

    }

    return true;

}

int main() {

    while (resuelve());

    return 0;

}
