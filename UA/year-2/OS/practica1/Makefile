# Makefile adaptado para subcarpetas

CC = gcc
CFLAGS = -std=c99

.DEFAULT_GOAL := help

# Compilar cualquier archivo .c en cualquier subcarpeta
%: %.c
	$(CC) $(CFLAGS) -o $@ $<
	@echo "Compilado exitosamente: $@"

# Compilar todos los .c en subcarpetas
all:
	@find . -name '*.c' | while read file; do \
    	exe=$${file%.c}; \
    	echo "Compilando $$file -> $$exe"; \
    	$(CC) $(CFLAGS) -o "$$exe" "$$file"; \
	done
	@echo "Todos los archivos compilados"

# Ejecutar un programa compilado
run-%:
	@if [ ! -f "$*" ]; then \
    	echo "Error: El binario $* no existe. Compile primero con 'make $*'"; \
    	exit 1; \
	fi
	./$*

clean:
	@find . -type f -perm +111 -not -name '*.c' -not -name 'Makefile' -not -name '*.pdf' -not -name '.clang-format' -exec rm -f {} +
	rm -rf *.dSYM
	@echo "Archivos limpiados"

help:
	@echo "Makefile para compilar programas C en subcarpetas"
	@echo ""
	@echo "Comandos disponibles:"
	@echo "  make ruta/ejecutable        - Compilar un archivo específico (ej: make ejemplos/1_procesos/creaproc1)"
	@echo "  make all                    - Compilar todos los archivos .c"
	@echo "  make run-ruta/ejecutable    - Ejecutar un programa compilado (ej: make run-ejemplos/1_procesos/creaproc1)"
	@echo "  make clean                  - Limpiar archivos compilados y debug"
	@echo "  make help                   - Mostrar esta ayuda"
	@echo ""

.PHONY: all clean help