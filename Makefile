CC=g++

CFLAGS=-c -std=c++0x
LFLAGS=-lSDL -lSDL_image

all: 8puzzle 

8puzzle: main.o Board.o Solver.o Draw.o Surface.o
	$(CC)  main.o Board.o Solver.o Draw.o Surface.o -o 8puzzle $(LFLAGS)

main.o: main.cpp 
	$(CC) $(CFLAGS) main.cpp  

Board.o : Board.cpp
	$(CC) $(CFLAGS) Board.cpp

Solver.o : Solver.cpp
	$(CC) $(CFLAGS) Solver.cpp

Draw.o : Draw.cpp
	$(CC) $(CFLAGS) Draw.cpp

Surface.o : Surface.cpp
	$(CC) $(CFLAGS) Surface.cpp

clean:
	rm  *.o
