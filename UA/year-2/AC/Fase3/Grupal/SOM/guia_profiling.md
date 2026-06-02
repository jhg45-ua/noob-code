# 🚀 Guía Definitiva: Análisis y Optimización de Kernels con NVIDIA Nsight Compute (NCU)

Esta guía documenta el flujo de trabajo completo, la interpretación de métricas a bajo nivel y la gestión de reportes para maximizar el rendimiento de arquitecturas GPU masivamente paralelas. [cite_start]Está orientada a la identificación de cuellos de botella y la preparación de memorias técnicas para entornos competitivos de alto rendimiento[cite: 4012].

---

## FASE 1: Preparación, Compilación y Captura

Para que Nsight Compute (NCU) pueda hacer una autopsia precisa y relacionar los atascos de hardware con líneas exactas de código C++, la fase de compilación es crítica.

### 1.1. La Compilación Estratégica
Si buscas perfilar rendimiento, evita compilar con `Debug` (`-G`), porque desactiva las optimizaciones de device code y NVIDIA no lo recomienda para profiling.
* **Comando ideal:** Debes compilar en `Release` (`-O3`) y añadir el flag `-lineinfo`.
    ```bash
    nvcc -O3 -lineinfo kernel.cu -o ejecutable.exe
    ```
* **¿Por qué `-lineinfo`?** Este flag inyecta metadatos en el binario que asocian las instrucciones en lenguaje ensamblador de la GPU (SASS) con tus líneas originales de C++, sin penalizar el rendimiento. NVIDIA lo recomienda para profiling y para usar la vista *Source* de NCU.

### 1.2. Captura Total: Consola vs. Interfaz Gráfica (GUI)

Para obtener un análisis completo, necesitamos obligar a la herramienta a ejecutar el kernel múltiples veces (*replay*) y leer todos los contadores físicos de los Streaming Multiprocessors (SM).

**Opción A: Desde la Consola (Recomendado para fluidez en el laboratorio)**
* **El comando base:**
    ```bash
    ncu --set full -o reporte_v1 .\ejecutable.exe
    ```
* **`--set full`:** Activa la recolección del conjunto completo de secciones predefinidas. Es más completo que `basic`, pero no significa “todas las métricas posibles”; la cobertura exacta depende de la GPU y de las secciones disponibles.
* **`-o reporte_v1`:** Genera el archivo `reporte_v1.ncu-rep` que luego abriremos en la interfaz visual (`ncu-ui`).

**Opción B: Desde la Interfaz Gráfica (`ncu-ui`)**
1. Abre la aplicación **Nsight Compute**.
2. Haz clic en **Create New Project** en la pantalla de inicio (o ve a **Connection** > **Connect**).
3. **Pestaña Executable:** * En **Application Executable**, introduce la ruta completa a tu `ejecutable.exe`.
   * En **Working Directory**, pon la carpeta donde están tus ficheros de entrada (ej. `.som` y `.pat`).
4. **Pestaña Output (Vital):**
   * En el campo **Output File**, especifica una ruta y nombre para guardar el reporte. *Si dejas esto en blanco, los datos vivirán solo en la RAM y se perderán al cerrar la aplicación.*
5. **Pestaña Activity (El equivalente a `--set full`):**
   * Busca el desplegable llamado **Section Set** o **Metrics**.
   * Cambia el valor por defecto a **Full**.
6. **Lanzamiento:** Haz clic en el botón azul **Launch** (abajo a la derecha). 

---

## FASE 2: Disección del Hardware (Interpretando los Datos)

Una vez tengas tu archivo `.ncu-rep` cargado en la interfaz, dirígete a la pestaña **Details**. Sigue este orden de análisis estricto:

### 2.1. GPU Speed Of Light (SOL) DOMAIN
Es el diagnóstico de alto nivel. Te indica qué recurso de la arquitectura está actuando como techo de cristal.
* **Metricas recomendadas:** Usa `sm__throughput.avg.pct_of_peak_sustained_active` como referencia principal para compute y las métricas equivalentes de memoria dentro de la sección SpeedOfLight. Si quieres ver los contribuyentes, añade `breakdown:sm__throughput`.
* **Memory [%]:** Si este valor supera el 80%, suele ser una señal de que tu kernel está cerca de estar **Memory Bound**. Es una heurística útil, no una regla dura.
* **SM [%] (Compute):** Si supera el 80%, suele indicar que estás cerca de estar **Compute Bound**. También aquí conviene tratarlo como guía práctica, no como umbral absoluto.
* **Cómo decidir el siguiente análisis:** Si el techo dominante parece ser memoria, pasa a **Memory Workload Analysis**. Si el techo dominante parece ser compute o ejecución de pipelines, pasa a **Compute Workload Analysis** y revisa después el mix de instrucciones, los pipelines saturados y la correlación con Source.
* **El Modelo Roofline (Techo de Cristal):**
    * *Eje X (Aritmethic Intensity):* Operaciones matemáticas por cada byte leído de memoria.
    * *Eje Y (Performance):* Rendimiento total.
    * *Lectura:* Si tu punto cae bajo la línea diagonal ascendente, normalmente estás limitado por el ancho de banda. Si tu punto choca contra la línea horizontal superior, normalmente tu límite es la capacidad de cálculo.

### 2.2. Compute Workload Analysis
Si tu kernel parece **Compute Bound**, esta sección te ayuda a entender qué tipo de cálculo está saturando la GPU y si el problema está en el mix de instrucciones, en el uso desigual de pipelines o en el reparto de trabajo.
* **Qué revisar primero:** la sección **Compute Workload Analysis**, la sección **Instruction Stats** y la vista **Source**.
* **Métricas y datos útiles:** el IPC/throughput de cómputo, el mix de instrucciones SASS, la utilización de pipelines y las métricas de source que relacionan instrucciones ejecutadas con líneas de código.
* **Cuándo usarla:** cuando `SM [%]` es claramente el dominante en SOL o cuando Roofline muestra el kernel pegado al techo superior, pero la parte de memoria no aparece como el factor limitante principal.
* **Qué suele indicar un problema:** un pipeline concreto muy saturado, un mix muy sesgado de instrucciones, demasiadas dependencias entre operaciones o una poca variedad de unidades de ejecución activas.

### 2.3. Memory Workload Analysis
Si eres *Memory Bound*, esta sección detalla dónde se pierden los ciclos.
* **Grupos de métricas recomendados:** `group:memory__chart`, `group:memory__first_level_cache_table`, `group:memory__l2_cache_table`, `group:memory__shared_table` y `group:memory__dram_table`.
* **L1/TEX Hit Rate:** El porcentaje de veces que un dato solicitado ya estaba en la Caché L1/TEX. Un porcentaje bajo suele indicar un patrón de acceso a memoria menos eficiente, aunque no siempre significa automáticamente que el acceso sea no coalescente.
* **Sectors/Req:** En L1/TEX y L2, este valor es especialmente útil para ver si los accesos están bien coalescidos. Para warps completos, valores más altos suelen significar más tráfico y peor eficiencia de acceso.
* **% Peak y Wavefront % Peak:** Son útiles para detectar saturación de un sub-sistema, pero no significan por sí solos que el patrón sea bueno. Úsalos junto con hit rate y sectors/request.
* **Diagrama de Flujo:** Observa los enlaces entre la *Global Memory*, *L2*, *L1* y *Registers*. Los anchos de las líneas y sus colores te indican visualmente dónde se está formando el embudo térmico o de datos.

### 2.4. Warp State Statistics (La Causa de los Atascos)
Analiza por qué los *warps* (grupos de 32 hilos) no están ejecutando instrucciones y pasan ciclos en estado de "espera" (*Stall*).
* **Métrica canónica:** `group:smsp__pcsamp_warp_stall_reasons`.
* **Stall Long Scoreboard:** Esperando una dependencia de L1TEX, que puede venir de global, local, surface o texture. *Solución: Mejorar el patrón de acceso, aumentar localización de datos o mover datos reutilizados a Shared Memory cuando tenga sentido.*
* **Stall Short Scoreboard:** Esperando una dependencia de MIO, típicamente asociada a shared memory, instrucciones matemáticas especiales o branching dinámico; en algunos casos aparece por conflictos de bancos.
* **Stall Math Pipe Throttle:** Las unidades matemáticas están saturadas. *Solución: Revisar el mix de instrucciones y, si la precisión lo permite, usar opciones o intrínsecos de menor coste.*
* **Stall Wait:** Es un estado de latencia fija o dependencia de ejecución; no debe interpretarse solo como barrera de sincronización.
* **Para análisis puntual en Source:** `smsp__pcsamp_warps_issue_stalled_long_scoreboard`, `smsp__pcsamp_warps_issue_stalled_short_scoreboard`, `smsp__pcsamp_warps_issue_stalled_math_pipe_throttle`, `smsp__pcsamp_warps_issue_stalled_wait`.

### 2.5. Occupancy (Ocupación)
Mide la eficiencia con la que mantienes llenos los Streaming Multiprocessors (SMs).
* **Métricas canónicas:** `launch__occupancy_per_register_count`, `launch__occupancy_per_shared_mem_size`, `launch__occupancy_limit_registers`, `launch__occupancy_limit_shared_mem`, `launch__occupancy_limit_warps`, `launch__waves_per_multiprocessor` y `sm__maximum_warps_per_active_cycle_pct`.
* **Theoretical Occupancy:** El límite máximo de *warps* que tu hardware podría albergar dadas las limitaciones de tu código y del hardware (registros, memoria compartida, bloques, barreras, etc.).
* **Achieved Occupancy:** La ocupación real. Si es drásticamente menor que la teórica, puede haber un problema de recursos, de tamaño de bloque o de balanceo de carga; no siempre indica por sí sola un mal reparto.
* **Regla práctica:** si la ocupación baja está acompañada de `not_selected` alto en Warp State Statistics, ya tienes indicio de que sí falta paralelismo efectivo; si no, puede ser solo un límite estructural del kernel.

---

## FASE 3: Herramientas Avanzadas para la Optimización

### 3.1. NVIDIA Occupancy Calculator (El Simulador)
Dentro de la sección de ocupación de NCU, existe una calculadora interactiva. Un SM tiene límites estrictos (ej. 64K registros en la arquitectura Ampere).
* **¿Para qué sirve?** Te permite estimar el impacto de cambios sin tocar C++.
* **Ejemplo de uso:** Si el reporte indica que cada hilo usa 40 registros, la calculadora puede ayudarte a estimar si bajar ese uso permitiría al SM alojar más warps o bloques.
* **Métrica de apoyo:** `launch__registers_per_thread` y `launch__shared_mem_per_block`.

### 3.2. La vista "Source" (El Francotirador)
Si compilaste con `-lineinfo`, ve al menú superior izquierdo dentro de *Details* y cambia de `Summary/Details` a `Source`.
* Verás tu código C++ emparejado línea a línea con las instrucciones SASS de la GPU.
* **El Mapa de Calor:** A la derecha, NCU marca con barras rojas las líneas exactas que producen los altos niveles de *Stalls*.
* **Métricas de apoyo:** `derived__avg_thread_executed`, `derived__avg_thread_executed_true`, `smsp__pcsamp_sample_count`, `thread_inst_executed`, `thread_inst_executed_true` y `sass__inst_executed_per_opcode_category`.

---

## FASE 4: Flujo de Trabajo en Equipo y Repositorio

Los archivos `.ncu-rep` son binarios pesados. Evita subir capturas redundantes al repositorio Git para no saturar el historial.

### 4.1. Estructura de Directorios Recomendada
```text
/Grupal/SOM/
├── src/                  # Código fuente (.cu, .h)
├── data/                 # Ficheros de entrada (.som, .pat)
└── profiling/
    ├── baselines.csv     # Exportación de tiempos tabulados
    ├── v1_naive.pdf      # Exportación del reporte base (Para la Memoria)
    └── vX_optima.pdf     # Exportación del reporte final optimizado

```

### 4.2. Exportación a PDF para la Memoria de la Asignatura

1. Abre tu `.ncu-rep` en `ncu-ui`.
2. Ve al icono de la esquina superior derecha y selecciona **Export > PDF**.
3. Guarda el PDF en la carpeta `profiling/`. Esto es clave para justificar técnicamente el rendimiento incluyendo gráficas de alta calidad (como el *Roofline Model*) en el entregable final.
4. Si necesitas correlación fuente/SASS en el reporte, compila con `-lineinfo` y, si trabajas desde la CLI, usa `--import-source` o `--source-folders` para importar el código fuente al reporte.



### 4.3. Comparativa de Baselines (El Método Empírico)

1. Haz una captura y pulsa el botón **Add Baseline** (icono de chincheta).
2. Haz **una única modificación** en el código.
3. Recompila, captura y abre el nuevo archivo. Nsight superpondrá los colores, permitiéndote demostrar con porcentajes si la modificación surtió efecto.

---

## FASE 5: Estrategia Definitiva para el Clasificador SOM (Cudathon)

A diferencia de una simple suma de vectores, la búsqueda de la neurona ganadora en el mapa auto-organizativo (SOM)  requiere un enfoque de rendimiento muy distinto:

1. **Explotar la Memoria Compartida (`__shared__`):** Los patrones de entrada se leen repetidamente contra todas las neuronas. Cargar el patrón actual en Shared Memory puede reducir tráfico global y mejorar la localización de datos, aunque no garantiza eliminar por completo los bloqueos por *Stall Long Scoreboard*.


2.  **Intensidad Aritmética Superior:** El cálculo de la distancia euclídea (restas, multiplicaciones, acumulaciones) puede aumentar la intensidad aritmética y mover el kernel hacia la derecha en el *Roofline Model*. El objetivo es equilibrar el uso de ALUs y memoria.


3. **Reducciones Paralelas:** Para encontrar la neurona ganadora en el mapa (el mínimo de las distancias), implementa una reducción paralela en árbol dentro de cada bloque, minimizando el trabajo secuencial y evitando cuellos de botella innecesarios en memoria global o en el host.



> **Regla de Oro de la Optimización:** Detente cuando alcances el límite físico que el modelo y las mediciones muestran con claridad. Si tu *Roofline* se aproxima a las líneas arquitectónicas y tu *Occupancy* es estable, probablemente estés cerca del techo práctico de ese kernel.

### 5.2. Comandos de Perfilado Recomendados
Para que la guía quede alineada con lo que suele ser más útil observar, usa estos perfiles base:

```bash
ncu --set full -o reporte_full ./ejecutable.exe
```

```bash
ncu --metrics sm__throughput.avg.pct_of_peak_sustained_active,breakdown:sm__throughput,group:memory__chart,group:memory__first_level_cache_table,group:memory__l2_cache_table,group:memory__shared_table,group:memory__dram_table,group:smsp__pcsamp_warp_stall_reasons -o reporte_metricas ./ejecutable.exe
```

```bash
nvcc -O3 -lineinfo kernel.cu -o ejecutable.exe
```

```bash
ncu --import-source --open-in-ui -o reporte_fuente ./ejecutable.exe
```