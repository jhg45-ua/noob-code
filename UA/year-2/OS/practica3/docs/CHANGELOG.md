# Changelog {#changelog}

Todos los cambios notables de este proyecto se documentan aquí.

El formato está basado en [Keep a Changelog](https://keepachangelog.com/es-ES/1.0.0/).

## [1.0.1] - 2025-12-19

### Corregido
- TUI ahora se ejecuta **después** de cerrar la GUI (antes era en paralelo)
- Añadido `system("clear")` para limpiar la consola al iniciar TUI
- Añadido prompt "Presiona ENTER para continuar..." en modo paso a paso
- Corregida inicialización de variable `tiempo_total`

### Mejorado
- Mejor experiencia de usuario: flujo secuencial GUI → TUI

---

## [1.0.0] - 2025-12-19

### Añadido
- Simulador de memoria con particiones variables
- Algoritmo **First Fit** (Primer Hueco)
- Algoritmo **Next Fit** (Siguiente Hueco)
- Interfaz gráfica con Raylib
  - Visualización de barra de memoria con colores
  - Lista de procesos y su estado
  - Controles interactivos (ESPACIO, P, R, ESC)
  - Auto-play con velocidad configurable
- Interfaz de terminal (TUI) para depuración
- Sistema de logging a archivo (`particiones.txt`)
- Compactación automática de huecos adyacentes
- Alineación de memoria a múltiplos de 100
- Ejecución paralela con `fork()` (GUI hijo, TUI padre)
- Documentación completa con Doxygen
  - Grafos de llamadas (call graphs)
  - Navegador de código fuente
  - Página principal con README

### Características Técnicas
- Uso de llamadas POSIX (`open`, `read`, `write`, `fork`)
- Memoria máxima: 2000 unidades
- Hasta 50 particiones simultáneas
- Hasta 100 procesos por simulación

---

## Pendiente (TODO)

### Algoritmos
- [ ] Best Fit (Mejor Hueco)
- [ ] Worst Fit (Peor Hueco)

### Estadísticas
- [ ] Cálculo de fragmentación externa
- [ ] Tiempo medio de espera
- [ ] Tiempo medio de retorno
- [ ] Uso de memoria a lo largo del tiempo

### Interfaz
- [ ] Cargar archivo de entrada desde GUI (file picker)
- [ ] Selector de algoritmo en GUI
- [ ] Modo paso a paso con retroceso (undo)
- [ ] Zoom en la barra de memoria
- [ ] Exportar estadísticas a CSV

### Testing
- [ ] Tests unitarios con CUnit o similar
- [ ] Tests de regresión para algoritmos

---

## Notas de Desarrollo

### Estructura del proyecto

```
practica3/
├── src/           # Código fuente
├── docs/          # Documentación
├── build/         # Archivos compilados
└── entrada.txt    # Archivo de prueba
```

### Generar documentación

```bash
doxygen Doxyfile
open docs/html/index.html
```
