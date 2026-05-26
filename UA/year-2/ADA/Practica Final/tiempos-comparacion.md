# Tiempos de Comparacion

Esta pruebas se esta realizando en los ordenadores de la sala de estudios de la politecnica IV que cuentan con una CPU 13th Gen Intel(R) Core(TM) i5-13500 y 16GB de RAM

En estas pruebas se compara tres tipos de cola en el mapa `500-bb.maze`

## Metodologia
Se realizan 6 ejecucciones y se descarta la primera, de las 5 restantes se realiza una media

## Priority Queue
```bash
alumno@clLLIBRE4-6:~/noob-code/UA/year-2/ADA/Practica Final$ ./maze_bb -f maze-BB-testfiles/500-bb.maze
5303
287313 35974 1 37435 213904 59 1 0
4.68811
alumno@clLLIBRE4-6:~/noob-code/UA/year-2/ADA/Practica Final$ ./maze_bb -f maze-BB-testfiles/500-bb.maze
5303
287313 35974 1 37435 213904 59 1 0
4.60714
alumno@clLLIBRE4-6:~/noob-code/UA/year-2/ADA/Practica Final$ ./maze_bb -f maze-BB-testfiles/500-bb.maze
5303
287313 35974 1 37435 213904 59 1 0
4.63496
alumno@clLLIBRE4-6:~/noob-code/UA/year-2/ADA/Practica Final$ ./maze_bb -f maze-BB-testfiles/500-bb.maze
5303
287313 35974 1 37435 213904 59 1 0
4.68077
alumno@clLLIBRE4-6:~/noob-code/UA/year-2/ADA/Practica Final$ ./maze_bb -f maze-BB-testfiles/500-bb.maze
5303
287313 35974 1 37435 213904 59 1 0
4.61123
```
## FIFO
```bash
alumno@clLLIBRE4-6:~/noob-code/UA/year-2/ADA/Practica Final$ ./maze_bb -f maze-BB-testfiles/500-bb.maze
5303
277553 34715 1 35972 206866 20 1 0
3.66911
alumno@clLLIBRE4-6:~/noob-code/UA/year-2/ADA/Practica Final$ ./maze_bb -f maze-BB-testfiles/500-bb.maze
5303
277553 34715 1 35972 206866 20 1 0
2.80627
alumno@clLLIBRE4-6:~/noob-code/UA/year-2/ADA/Practica Final$ ./maze_bb -f maze-BB-testfiles/500-bb.maze
5303
277553 34715 1 35972 206866 20 1 0
2.90285
alumno@clLLIBRE4-6:~/noob-code/UA/year-2/ADA/Practica Final$ ./maze_bb -f maze-BB-testfiles/500-bb.maze
5303
277553 34715 1 35972 206866 20 1 0
2.7365
alumno@clLLIBRE4-6:~/noob-code/UA/year-2/ADA/Practica Final$ ./maze_bb -f maze-BB-testfiles/500-bb.maze
5303
277553 34715 1 35972 206866 20 1 0
2.8001
```
## LIFO
```bash
alumno@clLLIBRE4-6:~/noob-code/UA/year-2/ADA/Practica Final$ ./maze_bb -f maze-BB-testfiles/500-bb.maze
5303
1204657273 150639938 8245 156791645 897225690 49534 8245 0
6904.25
alumno@clLLIBRE4-6:~/noob-code/UA/year-2/ADA/Practica Final$ ./maze_bb -f maze-BB-testfiles/500-bb.maze
5303
1204657273 150639938 8245 156791645 897225690 49534 8245 0
6881.93
alumno@clLLIBRE4-6:~/noob-code/UA/year-2/ADA/Practica Final$ ./maze_bb -f maze-BB-testfiles/500-bb.maze
5303
1204657273 150639938 8245 156791645 897225690 49534 8245 0
6855.56
alumno@clLLIBRE4-6:~/noob-code/UA/year-2/ADA/Practica Final$ ./maze_bb -f maze-BB-testfiles/500-bb.maze
5303
1204657273 150639938 8245 156791645 897225690 49534 8245 0
6892.83
alumno@clLLIBRE4-6:~/noob-code/UA/year-2/ADA/Practica Final$ ./maze_bb -f maze-BB-testfiles/500-bb.maze
5303
1204657273 150639938 8245 156791645 897225690 49534 8245 0
6867.55
alumno@clLLIBRE4-6:~/noob-code/UA/year-2/ADA/Practica Final$ ./maze_bb -f maze-BB-testfiles/500-bb.maze
5303
1204657273 150639938 8245 156791645 897225690 49534 8245 0
6956.52
```