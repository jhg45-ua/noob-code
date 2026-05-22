# Memoria Fase 3 (SOM CUDA)

## Requisitos
- TeX Live con `latexmk` y `xelatex`

## Compilación rápida
Desde la raíz del repositorio:

```bash
latexmk -xelatex -interaction=nonstopmode -halt-on-error docs/memoria-fase3/main.tex
```

Esto generará `main.pdf` en el directorio desde el que se ejecuta el comando.

## Compilación recomendada (salida local en la carpeta de memoria)

```bash
cd docs/memoria-fase3
latexmk -xelatex -interaction=nonstopmode -halt-on-error main.tex
```

Salida esperada:
- `docs/memoria-fase3/main.pdf`

## Limpieza de artefactos

```bash
cd docs/memoria-fase3
latexmk -c
```
