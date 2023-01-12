.PHONY: all clean
COMPILER = gcc
FLAGS = -Wall -g

all: main

main: main.o graph.o
	$(COMPILER) $(FLAGS) main.o graph.o -o main

main.o: main.c graph.h
	$(COMPILER) -c $(FLAGS) main.c

graph.o: graph.c graph.h
	$(COMPILER) -c $(FLAGS) graph.c

clean:
	rm -f *.o main
