CC = gcc
CFLAGS = -Wall

P1_DIR = practica1/48795869N-p1
P2_DIR = practica2/48795869N-p2
LIBS_DIR = lib

all: copia

file_utils.o: $(LIBS_DIR)/file_utils.c $(LIBS_DIR)/file_utils.h
	$(CC) $(CFLAGS) -c $(LIBS_DIR)/file_utils.c -o $(LIBS_DIR)/file_utils.o

copia: file_utils.o
	$(CC) $(CFLAGS) -o $(P1_DIR)/copia $(P1_DIR)/copia.c $(LIBS_DIR)/file_utils.o

clean:
	rm -f $(LIBS_DIR)/file_utils.o $(P1_DIR)/copia

.PHONY: all clean
