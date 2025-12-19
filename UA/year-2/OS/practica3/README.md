# Gestomemoria - Simulador de Gestión de Memoria {#mainpage}

![C](https://img.shields.io/badge/C-17-blue)
![Raylib](https://img.shields.io/badge/Raylib-4.5-green)
![Platform](https://img.shields.io/badge/Platform-macOS%20%7C%20Linux-lightgrey)

## Descripción

Simulador visual de algoritmos de gestión de memoria dinámica con particiones variables.
Proyecto de la asignatura **Sistemas Operativos** - Universidad de Alicante.

## 🚀 Inicio Rápido

```bash
# Compilar
mkdir build && cd build
cmake .. && make

# Ejecutar
./gestomemoria
```

## 📖 Documentación

- [Guía de Instalación](INSTALL.md)
- [Arquitectura del Sistema](ARCHITECTURE.md)
- [Changelog](CHANGELOG.md)

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

El programa ejecuta dos procesos de forma secuencial:
1. **Proceso hijo**: Interfaz gráfica (GUI) con Raylib
2. **Proceso padre**: Espera a que la GUI termine, luego ejecuta la TUI para depuración

> **Nota**: Cierra la ventana de la GUI para iniciar la TUI en terminal

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
practica3/
├── src/
│   ├── main.c          # Punto de entrada, GUI (hijo) y TUI (padre)
│   ├── sim_engine.c/h  # Motor de simulación
│   └── ficheros.c/h    # Entrada/Salida de archivos
├── docs/
│   ├── INSTALL.md      # Guía de instalación
│   ├── ARCHITECTURE.md # Arquitectura del sistema
│   └── CHANGELOG.md    # Historial de cambios
├── entrada.txt         # Archivo de procesos de ejemplo
├── CMakeLists.txt      # Configuración de CMake
├── Doxyfile            # Configuración de Doxygen
└── README.md           # Este archivo
```

## Constantes de Configuración

| Constante | Valor | Descripción |
|-----------|-------|-------------|
| `MEMORIA_TOTAL` | 2000 | Tamaño total de memoria simulada |
| `UNIDAD_MINIMA` | 100 | Alineación mínima de asignación |
| `MAX_PARTICIONES` | 50 | Máximo de particiones simultáneas |
| `MAX_PROCESOS` | 100 | Máximo de procesos en simulación |

## 📊 Estadísticas Futuras

- Fragmentación externa
- Tiempo medio de espera
- Uso de memoria a lo largo del tiempo

## Autor

**Julian Hinojosa Gil** - 2025

## Licencia

Proyecto académico - Universidad de Alicante

## Licencia

Proyecto académico - Universidad de Alicante
