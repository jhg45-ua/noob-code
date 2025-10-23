# Makefile adaptado para subcarpetas, binarios en raíz

CC = gcc
CFLAGS = -std=c99

.DEFAULT_GOAL := help

# Compilar cualquier archivo .c en cualquier subcarpeta, binario en raíz
%: %.c
	$(CC) $(CFLAGS) -o $(notdir $*) $<
	@echo "Compilado exitosamente: $(notdir $*)"

# Compilar todos los .c en subcarpetas, binarios en raíz
all:
	@find . -name '*.c' | while read file; do \
    	exe=$$(basename $${file%.c}); \
    	echo "Compilando $$file -> $$exe"; \
    	$(CC) $(CFLAGS) -o "$$exe" "$$file"; \
	done
	@echo "Todos los archivos compilados en el directorio raíz"

# Ejecutar un programa compilado desde la raíz
run-%:
	@if [ ! -f "$(notdir $*)" ]; then \
    	echo "Error: El binario $(notdir $*) no existe. Compile primero con 'make $*'"; \
    	exit 1; \
	fi
	./$(notdir $*)

clean:
	@find . -type f -perm +111 -not -name '*.c' -not -name 'Makefile' -not -name '*.pdf' -not -name '.clang-format' -exec rm -f {} +
	rm -rf *.dSYM
	@echo "Archivos limpiados"

help:
	@echo "Makefile para compilar programas C en subcarpetas, binarios en raíz"
	@echo ""
	@echo "Comandos disponibles:"
	@echo "  make ruta/ejecutable        - Compilar un archivo específico (ej: make ejemplos/1_procesos/creaproc1)"
	@echo "  make all                    - Compilar todos los archivos .c (binarios en raíz)"
	@echo "  make run-ejecutable         - Ejecutar un programa compilado desde la raíz (ej: make run-creaproc1)"
	@echo "  make clean                  - Limpiar archivos compilados y debug"
	@echo "  make help                   - Mostrar esta ayuda"
	@echo ""

.PHONY: all clean help
