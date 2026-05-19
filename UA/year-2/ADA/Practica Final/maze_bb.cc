// Julian Hinojosa Gil, 48795869N
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <limits>
#include <chrono>

// Macro para representar el infinito, es el valor máximo de long, que es el tipo que usamos para los costes.
#define INFINITO std::numeric_limits<long>::max()


// Estructura que representa los argumentos de la linea de comandos
struct args {
    bool p2D = false;       // Muestra el laberinto con la solución marcada
    bool p = false;         // Muestra la ruta exacta seguida por la solución
    std::string filename;   // Nombre del archivo que contiene el laberinto
};

// Estructura para almacenar las estadísticas del algoritmo
struct Stats {
    long visitados = 0;
    long explorados = 0;
    long hojas = 0;
    long descartados_no_factibles = 0;
    long descartados_no_prometedores = 0;
    long prometedores_descartados = 0;
    long actualizaciones_desde_hoja = 0;    
    long actualizaciones_desde_cota = 0;
};

struct Nodo {
    int i, j;                   // Dónde estoy
    long coste_acumulado;       // Pasos que he dado hasta llegar aquí (tu antigua 'k')
    long cota_optimista;        // Heurística: (coste_acumulado + estimación hasta la meta)
    std::vector<unsigned> ruta; // El historial exacto de movimientos para llegar aquí

    // Queremos sacar siempre el camino con MENOR cota optimista,
    // invertimos el operador (ponemos > en lugar de <).
    bool operator>(const Nodo& otro) const {
        return cota_optimista > otro.cota_optimista;
    }
};

void mostrar_uso() {
    std::cerr << "Usage:\nmaze_bb [-p] [--p2D] -f file" << std::endl;
}

void maze_parser(int argc, char* argv[], args& arguments) {
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "--p2D") {
            arguments.p2D = true;
        } else if (std::string(argv[i]) == "-p") {
            arguments.p = true;
        } else if (std::string(argv[i]) == "-f") {
            if (i + 1 < argc) {
                arguments.filename = argv[++i];
            } else {
                std::cerr << "ERROR: missing filename." << std::endl;
                mostrar_uso();
                exit(1);
            }
        } else {
            std::cerr << "ERROR: unknown option " << argv[i] << "." << std::endl;
            mostrar_uso();
            exit(1);
        }
    }
    if (arguments.filename.empty()) {
        std::cerr << "ERROR: missing filename." << std::endl;
        mostrar_uso();
        exit(1);
    }
}

void leer_laberinto(const std::string& filename, int& n, int& m, std::vector<std::vector<int>>& maze) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "ERROR: can't open file: " << filename << "." << std::endl;
        mostrar_uso();
        exit(1);
    }

    file >> n >> m;
    maze.resize(n, std::vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            file >> maze[i][j];
        }
    }
}

// Orden de las direcciones a explorar: SE, S, E, SW, NE, W, NW, N
const std::vector<unsigned> orden_dirs = {4, 5, 3, 6, 2, 7, 1, 8};

// Matriz de incrementos para cada dirección (0 es un placeholder para facilitar el acceso)
const int dirs[9][2] = {
    {0, 0},
    {-1, 0}, // 1: N
    {-1, 1}, // 2: NE
    {0, 1},  // 3: E
    {1, 1},  // 4: SE
    {1, 0},  // 5: S
    {1, -1}, // 6: SW
    {0, -1}, // 7: W
    {-1, -1} // 8: NW
};

// Función de estimación heurística: Distancia de Chebyshev al destino
long estimacion(int filas, int columnas, int i, int j) {
    return std::max(filas - 1 - i, columnas - 1 - j);
}

void maze_bb(const std::vector<std::vector<int>>& maze,
             long& bestSol,
             std::vector<unsigned>& best_path,
             Stats& st) {
             
    int n = maze.size();
    int m = maze[0].size();

    // 1. Declarar la Lista de Nodos Vivos (LNV)
    std::priority_queue<Nodo, std::vector<Nodo>, std::greater<Nodo>> LNV;

    // 2. Crear nuestro primer explorador en la casilla (0,0)
    Nodo inicial;
    inicial.i = 0;
    inicial.j = 0;
    inicial.coste_acumulado = 1; // El primer paso cuenta
    inicial.ruta = {};
    inicial.cota_optimista = inicial.coste_acumulado + estimacion(n, m, 0, 0);

    // 3. Meterlo a la cola
    LNV.push(inicial);

    // (Asegúrate de declarar la matriz 'costs' al principio de tu función maze_bb 
    // para llevar el historial y evitar bucles infinitos)
    std::vector<std::vector<long>> costs(n, std::vector<long>(m, INFINITO));
    costs[0][0] = 1;

    // 4. EL BUCLE INFINITO
    while (!LNV.empty()) {
        // Sacamos al explorador con "mejor pinta" (menor cota optimista)
        Nodo actual = LNV.top();
        LNV.pop();

        // --- A) PODA TARDÍA (Prometedor pero descartado) ---
        // Cuando este nodo entró en la cola era bueno, pero mientras esperaba
        // alguien ha encontrado un récord (bestSol) mejor que su cota ideal.
        if (actual.cota_optimista >= bestSol) {
            st.prometedores_descartados++;
            continue; // Lo matamos y pasamos al siguiente
        }

        // --- B) ¿HEMOS LLEGADO A LA META? (Nodo Hoja) ---
        if (actual.i == n - 1 && actual.j == m - 1) {
            st.hojas++; // Hemos tocado el final
            
            // Si el coste real con el que hemos llegado mejora el récord mundial
            if (actual.coste_acumulado < bestSol) {
                bestSol = actual.coste_acumulado;
                best_path = actual.ruta;
                st.actualizaciones_desde_hoja++; 
            }
            // Aunque mejore o no el récord, desde la meta NO se explora más allá
            continue; 
        }

        // --- C) EXPANSIÓN DE LOS 8 VECINOS ---
        // Si no es la meta, nos paramos en la casilla y miramos a nuestro alrededor
        st.explorados++; 

        for (int p = 0; p < 8; p++) {
            unsigned direccion = orden_dirs[p];
            int isig = actual.i + dirs[direccion][0];
            int jsig = actual.j + dirs[direccion][1];

            // 1. ¿Es Factible? (No me salgo del mapa y es un 1)
            if (isig >= 0 && isig < n && jsig >= 0 && jsig < m && maze[isig][jsig] == 1) {
                
                long nuevo_coste = actual.coste_acumulado + 1;
                long nueva_cota = nuevo_coste + estimacion(n, m, isig, jsig);

                // 2. ¿Es Prometedor por Heurística Futura?
                if (nueva_cota < bestSol) {
                    
                    // 3. ¿Es Prometedor por Historial Pasado? (Evitar ciclos y rutas peores)
                    if (nuevo_coste < costs[isig][jsig]) {
                        
                        // ¡HA PASADO TODOS LOS FILTROS! 
                        // Actualizamos el historial para que nadie vuelva por un camino peor
                        costs[isig][jsig] = nuevo_coste;

                        // Creamos el nuevo estado (el hijo) copiando la mochila del padre
                        Nodo hijo;
                        hijo.i = isig;
                        hijo.j = jsig;
                        hijo.coste_acumulado = nuevo_coste;
                        hijo.cota_optimista = nueva_cota;
                        hijo.ruta = actual.ruta;           // Copiamos la ruta que llevaba el padre
                        hijo.ruta.push_back(direccion);    // Y le añadimos el nuevo paso
                        
                        // Lo metemos en la lista VIP. La cola lo ordenará mágicamente.
                        LNV.push(hijo);
                        st.visitados++; // Contabilizamos que hemos "tocado" un nodo válido

                    } else {
                        // Cortado por culpa del historial de la matriz 'costs'
                        st.descartados_no_prometedores++;
                    }
                } else {
                    // Cortado porque su estimación ideal ya es peor que nuestro bestSol
                    st.descartados_no_prometedores++;
                }
            } else {
                // Cortado por chocar con un muro o salirse del mapa
                st.descartados_no_factibles++;
            }
        }
    }
}

int main(int argc, char* argv[]) {

    // 1. Parseo de argumentos
    args arguments;
    maze_parser(argc, argv, arguments);

    // 2. Lectura del laberinto desde el archivo
    int n, m;
    std::vector<std::vector<int>> maze;
    leer_laberinto(arguments.filename, n, m, maze);

    // Caso especial: Si la celda de inicio es un muro, no hay solución posible, así que imprimimos los resultados correspondientes y salimos.
    if (maze[0][0] == 0) {
        std::cout << "0\n0 0 0 0 0 0 0 0\n0.0\n";
        if (arguments.p2D) std::cout << "0\n";
        if (arguments.p) std::cout << "<0>\n";
        return 0;
    }

    // 3. Inicialización de estructuras para el backtracking
    std::vector<std::vector<long>> costs(n, std::vector<long>(m, INFINITO));
    std::vector<unsigned> current_path; // Vector para la ruta activa
    std::vector<unsigned> best_path;    // Vector para la ruta ganadora
    Stats st;
    long bestSol = INFINITO;
    
    // 4. El coste para la celda de inicio es 1, ya que es el primer paso que damos (estamos en esa celda), y esto nos ayudará a evitar problemas con la estimación heurística y la comparación de costes.
    costs[0][0] = 1;

    // 5. Arrancamos el tiempo de ejecución del backtracking
    auto start = std::chrono::high_resolution_clock::now();

    // 6. Llamada inicial al backtracking, empezando desde la posición (0, 0) con un coste acumulado de 1 (la celda de inicio)
    maze_bb(maze, bestSol, best_path, st);

    // 7. Paramos el tiempo de ejecución del backtracking
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    // --- Construcción del string y dibujo sobre el mapa (Hacia adelante) ---
    std::string camino_str = "<";
    if (bestSol != INFINITO) {
        int curr_i = 0, curr_j = 0;
        maze[curr_i][curr_j] = 2; // Marcamos el origen
        
        // Recorremos los pasos exactos que guardó la ruta ganadora
        for (unsigned dir : best_path) {
            camino_str += std::to_string(dir);
            curr_i += dirs[dir][0];
            curr_j += dirs[dir][1];
            maze[curr_i][curr_j] = 2; // Marcamos el mapa
        }
    } else {
        camino_str += "0";
    }
    camino_str += ">";

    // --- Impresión ---
    std::cout << (bestSol == INFINITO ? 0 : bestSol) << std::endl;
    std::cout << st.visitados << " " << st.explorados << " " << st.hojas << " " 
              << st.descartados_no_factibles << " " << st.descartados_no_prometedores << " "
              << st.prometedores_descartados << " " << st.actualizaciones_desde_hoja << " " << st.actualizaciones_desde_cota << std::endl;
    std::cout << duration.count() << std::endl;

    if (arguments.p2D) {
        if (bestSol == INFINITO) {
            std::cout << "0" << std::endl;
        } else {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    std::cout << (maze[i][j] == 2 ? '*' : (maze[i][j] ? '1' : '0'));
                }
                std::cout << std::endl;
            }
        }
    }

    if (arguments.p) {
        std::cout << camino_str << std::endl;
    }

    return 0;
}