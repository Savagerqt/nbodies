CC=g++
CFLAGS=-lSDL2 -lm
OBJ=src/main.cpp src/quad.cpp src/generalbodies.cpp src/body.cpp src/initbodies.cpp

nbodies:
	$(CC) -D N=$(N) $(OBJ) -o out.o $(CFLAGS)
	./out.o
