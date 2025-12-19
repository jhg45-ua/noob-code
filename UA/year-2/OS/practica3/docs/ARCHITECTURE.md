# Arquitectura del Sistema {#architecture}

## Diagrama de Módulos

```
┌─────────────────────────────────────────────────────────┐
│                        main.c                           │
│  ┌─────────────────┐       ┌─────────────────────────┐  │
│  │   TUI (padre)   │       │      GUI (hijo)         │  │
│  │   test_sim()    │       │      run_gui()          │  │
│  └────────┬────────┘       └───────────┬─────────────┘  │
└───────────┼────────────────────────────┼────────────────┘
            │                            │
            ▼                            ▼
┌─────────────────────────────────────────────────────────┐
│                    sim_engine.c                         │
│  ┌──────────────┐ ┌──────────────┐ ┌──────────────────┐ │
│  │ Asignación   │ │ Liberación   │ │  Compactación    │ │
│  │ de memoria   │ │ de procesos  │ │  de huecos       │ │
│  └──────────────┘ └──────────────┘ └──────────────────┘ │
└─────────────────────────────────────────────────────────┘
            │                            │
            ▼                            ▼
┌─────────────────────────────────────────────────────────┐
│                     ficheros.c                          │
│  ┌──────────────────┐       ┌─────────────────────────┐ │
│  │ cargar_procesos  │       │    guardar_estado       │ │
│  │ (entrada.txt)    │       │    (particiones.txt)    │ │
│  └──────────────────┘       └─────────────────────────┘ │
└─────────────────────────────────────────────────────────┘
```

## Flujo de Ejecución

1. **Inicio**: `main()` ejecuta `fork()`
2. **Proceso hijo** (pid == 0): Ejecuta la GUI con Raylib
3. **Proceso padre** (pid > 0): Espera con `waitpid()` a que el hijo termine
4. **Después de cerrar GUI**: El padre ejecuta la TUI en terminal (modo paso a paso)
4. **Cada tick de simulación**:
   - Se envejecen los procesos en memoria (decrementan t_restante)
   - Se liberan procesos que han terminado (t_restante == 0)
   - Se intentan asignar procesos de la cola de espera
   - Se guarda el estado en el log

## Estructuras de Datos Principales

### Memoria

La estructura central que gestiona las particiones:

```c
typedef struct {
    Particion particiones[MAX_PARTICIONES];  // Array de particiones
    int cant_particiones;                     // Número actual
    int ultimo_indice_asignado;               // Para Next Fit
} Memoria;
```

### Proceso

Representa un proceso en la simulación:

```c
typedef struct {
    char nombre[10];      // Identificador único (ej: "P1")
    int t_llegada;        // Instante de llegada
    int mem_requerida;    // Memoria solicitada
    int t_ejecucion;      // Tiempo total de ejecución
    int t_restante;       // Ticks restantes
    bool en_memoria;      // ¿Está cargado?
    bool finalizado;      // ¿Ha terminado?
} Proceso;
```

### Partición

Representa un bloque de memoria (hueco o proceso):

```c
typedef struct {
    int dir_inicio;           // Dirección base
    int tamano;               // Tamaño del bloque
    int estado;               // 0=HUECO, 1=OCUPADO
    char nombre_proceso[10];  // Nombre o "HUECO"
} Particion;
```

## Algoritmos de Asignación

### First Fit (Primer Hueco)

Busca secuencialmente desde el inicio de la memoria:

```
Para i = 0 hasta cant_particiones:
    Si particiones[i].estado == HUECO Y 
       particiones[i].tamano >= mem_requerida:
        Retornar i
Retornar -1 (no encontrado)
```

**Ventajas**: Simple, rápido para memorias pequeñas
**Desventajas**: Fragmentación al inicio de la memoria

### Next Fit (Siguiente Hueco)

Busca desde la última posición asignada (circular):

```
inicio = ultimo_indice_asignado
Para j = 0 hasta cant_particiones:
    i = (inicio + j) % cant_particiones
    Si particiones[i].estado == HUECO Y 
       particiones[i].tamano >= mem_requerida:
        ultimo_indice_asignado = i
        Retornar i
Retornar -1 (no encontrado)
```

**Ventajas**: Distribuye mejor la fragmentación
**Desventajas**: Puede ser más lento en el peor caso

## Gestión de Memoria

### Alineación

Toda memoria se alinea a múltiplos de `UNIDAD_MINIMA` (100):

```c
// Ejemplo: solicitar 243 → se asignan 300
int alinear_size(int size) {
    int bloques = size / UNIDAD_MINIMA;
    if (size % UNIDAD_MINIMA != 0)
        bloques++;
    return bloques * UNIDAD_MINIMA;
}
```

### Compactación

Cuando se libera un proceso, se fusionan huecos adyacentes:

```
Para cada par de particiones consecutivas:
    Si ambas son HUECO:
        Fusionar (sumar tamaños)
        Eliminar la segunda
        Repetir desde el inicio
```

## Uso de fork()

El programa usa `fork()` para ejecutar GUI y TUI en paralelo:

```c
pid_t pid = fork();

if (pid == 0) {
    // Hijo: GUI con Raylib
    run_gui(&m, procesos, num_procesos);
    _exit(0);
} else {
    // Padre: TUI en terminal
    test_sim();
    waitpid(pid, NULL, 0);  // Esperar al hijo
}
```

Esto permite depurar en terminal mientras se visualiza en la GUI.
