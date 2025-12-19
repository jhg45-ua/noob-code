# Gestomemoria - Simulador de Gestión de Memoria {#mainpage}

## Descripción

Simulador visual de algoritmos de gestión de memoria dinámica con particiones variables.
Proyecto de la asignatura **Sistemas Operativos** - Universidad de Alicante.

## Algoritmos Implementados

| Algoritmo | Descripción |
|-----------|-------------|
| **First Fit** | Asigna el primer hueco que sea suficientemente grande |
| **Next Fit** | Como First Fit, pero empieza desde la última posición asignada |

## Requisitos

- CMake 3.11+
- [Raylib](https://www.raylib.com/) (para la interfaz gráfica)
- Compilador C con soporte C17

## Compilación

```bash
mkdir build && cd build
cmake ..
make
```

## Uso

```bash
./gestomemoria
```

### Controles (GUI)

| Tecla | Acción |
|-------|--------|
| `ESPACIO` | Avanzar un tick de simulación |
| `P` | Activar/desactivar reproducción automática |
| `R` | Reiniciar simulación |
| `ESC` | Salir |

## Formato del Archivo de Entrada

El archivo `entrada.txt` debe seguir este formato:

```
<nombre_proceso> <instante_llegada> <memoria_requerida> <tiempo_ejecucion>
```

### Ejemplo

```
P1 0 243 5
P2 1 150 3
P3 2 500 4
```

## Arquitectura del Proyecto

```
src/
├── main.c          # Punto de entrada, GUI (Raylib) y TUI
├── sim_engine.c/h  # Motor de simulación (asignación, liberación, compactación)
└── ficheros.c/h    # Entrada/Salida de archivos
```

## Constantes de Configuración

| Constante | Valor | Descripción |
|-----------|-------|-------------|
| `MEMORIA_TOTAL` | 2000 | Tamaño total de memoria simulada |
| `UNIDAD_MINIMA` | 100 | Alineación mínima de asignación |
| `MAX_PARTICIONES` | 50 | Máximo de particiones simultáneas |
| `MAX_PROCESOS` | 100 | Máximo de procesos en simulación |

## Autor

**Julian Hinojosa Gil** - 2025

## Licencia

Proyecto académico - Universidad de Alicante
