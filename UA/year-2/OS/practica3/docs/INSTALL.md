# Guía de Instalación {#install}

## macOS

### Instalar dependencias con Homebrew

```bash
# Instalar Raylib
brew install raylib

# Instalar CMake (si no lo tienes)
brew install cmake

# Opcional: Graphviz para generar documentación con diagramas
brew install graphviz
```

### Compilar el proyecto

```bash
cd /ruta/al/proyecto
mkdir build && cd build
cmake ..
make
```

### Ejecutar

```bash
./gestomemoria
```

## Linux (Ubuntu/Debian)

```bash
# Instalar dependencias
sudo apt update
sudo apt install cmake libraylib-dev

# Compilar
mkdir build && cd build
cmake ..
make
```

## Problemas comunes

### Error: "raylib not found"

Asegúrate de que Raylib está instalado correctamente:

```bash
# macOS
brew reinstall raylib

# Linux
sudo apt install libraylib-dev
```

### Error: "fork() failed"

El sistema no tiene recursos suficientes. Cierra otras aplicaciones.

### Error de compilación con C17

Asegúrate de tener un compilador compatible:

```bash
# macOS (Xcode Command Line Tools)
xcode-select --install

# Linux
sudo apt install build-essential
```
