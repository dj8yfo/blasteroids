CFLAGS=-g -Wall
all: game
%.o: %.c
	gcc  -c -I./headers $^ `pkg-config --libs allegro-5 allegro_primitives-5 allegro_image-5` -o $@
game: game.c spaceship.o locmath.o model.o subroutine.o keyboard.o
	gcc -I./headers subroutine.o model.o spaceship.o locmath.o keyboard.o game.c  -lm `pkg-config --libs allegro-5 allegro_primitives-5 allegro_image-5` -o game
clean:
	rm game
clean-all:
	rm *.o
	rm game
