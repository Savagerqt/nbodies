CC=g++
CFLAGS=-lSDL2 -lm
OBJ=src/main.cpp src/quad.cpp src/generalbodies.cpp src/body.cpp src/initbodies.cpp

nbodies:
	$(CC) $(OBJ) -o out.o $(CFLAGS)
