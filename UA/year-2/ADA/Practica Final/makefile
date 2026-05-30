# Julian Hinojosa Gil, 48795869N

OPTS = -Wall -Wextra -O3 -std=c++0x
CC = g++

all:  maze_bb

maze_bb: maze_bb.cc
	${CC} ${OPTS} -o maze_bb maze_bb.cc

tar: maze_bb.cc makefile
	tar cvfz 48795869N.tar.gz maze_bb.cc makefile

clean: 
	rm -rf maze_bb maze_bb.dSYM *~ 48795869N.tar.gz memoria/memoria.synctex.gz memoria/memoria.bbl memoria/memoria.pdf