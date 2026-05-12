# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

University lab (Fase 3 — Arquitectura de Computadores, Grado en Ingeniería Informática, UA) on GPU programming with CUDA. Two sub-projects:

- **Individual** (`Individual/vectoraddGPU/`): Vector addition on GPU, targeting GPGPU-Sim for simulation.
- **Grupal** (`Grupal/`): SOM (Self-Organizing Map) pattern classification parallelized on GPU. The group chose exercise **D — Clasificador paralelo basado en SOM** from the assignment options.

The group project has two copies of the CUDA source — `Grupal/clasificacionSOM.cu` (working copy) and `Grupal/SOM/src/clasificacionSOM.cu` (Visual Studio project copy); keep both in sync when editing.

**Constraint from the assignment:** existing functions (`ClasificacionSOMCPU`, `LeerSOM`, `LeerPatrones`, `runTest`, etc.) must not be modified. Only `ClasificacionSOMGPU` and its kernels are ours to implement.

## Build Commands

### Individual (vectoraddGPU) — Linux/GPGPU-Sim via Makefile

```bash
# From Individual/vectoraddGPU/
make            # compile only (creates build/vecadd)
make run        # compile + run under GPGPU-Sim, outputs to result/
make clean      # wipe build/ and result/
```

The Makefile assumes GPGPU-Sim is installed at `~/hpc_workspace/gpgpu-sim_distribution` and copies SM7_QV100 config files into `build/` before running.

### Grupal (SOM) — Windows Visual Studio

Open `Grupal/SOM/SOM.sln` in Visual Studio with CUDA toolkit installed. Build via the IDE (Debug or Release). The executable is invoked as:

```
SOM.exe <fichero.som> <fichero.pat>
```

Example data files (`peq.som`/`peq.pat`, `grande.som`/`grande.pat`, `patrones.pat`) are in `Grupal/SOM/` and `Grupal/`.

### Standalone CPU reference (M1) — Linux/Mac/Windows

The files `Grupal/io.c`, `Grupal/io.h`, `Grupal/som_cpu.c` implement a pure-C reference classifier that does not require CUDA or Visual Studio.

```bash
# Linux / Mac
gcc -O2 -o som_cpu Grupal/io.c Grupal/som_cpu.c -lm
./som_cpu Grupal/test/ejemplo.som Grupal/test/ejemplo.pat
# → escribe salida.txt y muestra resultados por stdout

# Windows (MSVC desde Developer Command Prompt)
cl /O2 io.c som_cpu.c
som_cpu.exe test\ejemplo.som test\ejemplo.pat
```

Use this to get the expected CPU output for any `.som`/`.pat` pair before comparing against the GPU implementation. The small example in `Grupal/test/` (SOM 3×2, 5 patrones, dim=3) has expected output in `test/salida_esperada.txt`.

## Architecture

### Individual — vecadd

- `src/vecadd.cu`: Defines the `vecadd` kernel using a **grid-stride loop** so each thread processes `COMPUTE_N_ELEMENTS_PER_THREAD` (8) elements. Grid is sized as `VECTOR_ELEMENTS / 8` total threads in blocks of 512. Measures GPU time (with and without H↔D transfer) vs CPU time.
- `src/vecadd_gold.cpp`: CPU reference (`computeGold`), used to verify GPU output.
- `src/vecadd.h`: Declares `computeGold`.

### Grupal — SOM classification

**Algorithm:** for every input pattern, find the neuron (BMU) whose weight vector, summed with its 4-directional cross-neighborhood (up/down/left/right, only if in bounds), gives the minimum total Euclidean distance to the pattern. Output is the label of the winning neuron.

The GPU implementation is split across four milestones (M1–M4):

| Milestone | Owner | Status | Responsibility |
|-----------|-------|--------|---------------|
| M1 | Jesús | **Complete** | I/O, CPU reference — standalone `io.c`/`io.h` + `som_cpu.c` |
| M2 | Abdallah | Done | CUDA memory management, `main()` orchestration |
| M3 | Ximo | **Complete** | `KernelDistanciasVecindario` — distances kernel |
| M4 | Julián | **Pending** | Argmin/reduction kernel — find winning neuron |

**M3 — `KernelDistanciasVecindario`** (implemented in `clasificacionSOM.cu`):
- 1 thread per neuron, 2D grid of 16×16 blocks.
- Loads the current pattern into `extern __shared__` memory cooperatively (all threads in the block share the load via stride loop), then calls `__syncthreads()`.
- Each thread computes `DistanciaEuclideaNeurona` for itself plus up to 4 valid neighbors, writes the sum to `dDistancias[indiceNeurona]`.
- Output: `dDistancias[totalNeuronas]` — one score per neuron for the current pattern.

**M4 — Reduction kernel** (NOT yet implemented):
- Must find the index of the minimum value in `dDistancias` (not just the value — the index is needed to look up `labels[winner]`).
- Recommended approach: tree reduction with `(value, index)` pairs in shared memory (`log₂(N)` steps). Quick alternative: `thrust::min_element`.
- **Critical:** cannot use `if (value < min)` naively across threads — that causes race conditions. Must use tree reduction with `__syncthreads()` barriers.
- Currently bypassed: `EtiquetaGPU[np] = EtiquetaCPU[np]` is a placeholder at line ~240.

### Memory layout convention (critical for GPU code)

Neuron `(y, x)` → linear index `y * ancho + x`. Weights for neuron `i` start at `i * dimension` in the flat array.
- `IndiceNeuronaRowMajor(y, x, ancho)` → `y * ancho + x`
- `IndicePesoRowMajor(indiceNeurona, dimension, componente)` → `indiceNeurona * dimension + componente`

The `TSOM` struct uses a 2D pointer (`TNeurona** Neurona`). `CopiarSOMLineal` flattens it to a contiguous host array before uploading to GPU — do not skip this step.

### Data flow (full pipeline)

```
fichero.som / fichero.pat
        │ LeerSOM / LeerPatrones (M1, harness)
        ▼
TSOM + TPatrones in RAM
        │ CopiarSOMLineal + cudaMemcpy (M2/M3)
        ▼
dPesosLineales + dPatronLineal in VRAM
        │ KernelDistanciasVecindario (M3)
        ▼
dDistancias[totalNeuronas] in VRAM
        │ argmin reduction kernel (M4 — PENDING)
        ▼
winner index → labels[winner] → EtiquetaGPU[np]
        │ cudaMemcpy back (M2)
        ▼
EtiquetaGPU[] compared vs EtiquetaCPU[] in runTest
```

### Correctness check

`runTest` compares `EtiquetaCPU[i]` vs `EtiquetaGPU[i]` for every pattern. A mismatch prints the pattern index and the expected label. Only GPU time is counted for the CUDAthon competition.

### Formato de ficheros de entrada/salida

**`.som`** — Mapa SOM:
```
Alto: <filas>
Ancho: <columnas>
Dimension: <dim>
N<x>,<y>: <w0> <w1> ... <wdim-1>   ← orden en fichero: x=1..Ancho (lento), y=1..Alto (rápido)
L<x>,<y>: <label>
...                                  ← los ids N/L en el fichero son decorativos, se ignoran
```
Las posiciones son `Neurona[y-1][x-1]` (harness) ↔ `pesos[(y-1)*ancho+(x-1)]` (flat). El parser ignora los identificadores `N<x>,<y>` y `L<x>,<y>` — el orden de los bloques en el fichero determina qué neurona es cuál.

**`.pat`** — Patrones de entrada:
```
Numero: <n>
Dimension: <dim>
P<n>: <w0> <w1> ... <wdim-1>
...
```

**`salida.txt`** — Salida de `escribir_resultados`:
```
P1: <label>
P2: <label>
...
```

### Common pitfalls (from task document)

- **Border neurons:** a corner neuron has 2 valid neighbors, an edge neuron has 3 — always check `i>0`, `i<alto-1`, `j>0`, `j<ancho-1` before adding each neighbor.
- **Reduction bug:** the argmin needs the *position* of the minimum, not its value; forgetting this gives wrong labels even when distances are correct.
- **Race conditions:** never update a shared minimum with a plain `if` across threads — use tree reduction in shared memory.
- **Struct divergence:** `clasificacionSOM.h` defines the actual structs used by the harness (`TSOM`, `TNeurona`, `TPatrones`); the flat GPU layout in `CopiarSOMLineal` is a separate copy specifically for the GPU — do not conflate them.
