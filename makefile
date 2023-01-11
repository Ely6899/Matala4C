.PHONY: all clean
COMPILER = gcc
FLAGS = -Wall -g

all: main

main: main.o edges.o nodes.o algo.o
	$(COMPILER) $(FLAGS) main.o edges.o nodes.o algo.o -o main

main.o: main.c
	$(COMPILER) -c $(FLAGS) main.c

algo.o: algo.c algo.h nodes.h edges.h
	$(COMPILER) -c $(FLAGS) algo.c

nodes.o: nodes.c edges.h
	$(COMPILER) -c $(FLAGS) nodes.c

edges.o: edges.c nodes.h
	$(COMPILER) -c $(FLAGS) edges.c

clean:
	rm -f *.o main
