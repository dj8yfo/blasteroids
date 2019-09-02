# CFLAGS=-g -Wall
CFLAGS=-g -Wall
all: game
%.o: %.c
	rc -c cc $(CFLAGS) -c -I./headers $^ `pkg-config --libs allegro-5 allegro_primitives-5 allegro_image-5` -o $@
	cc $(CFLAGS) -c -I./headers $^ `pkg-config --libs allegro-5 allegro_primitives-5 allegro_image-5` -o $@
game: spaceship.o linkedlist.o locmath.o blast.o model.o subroutine.o keyboard.o game.c
	rc -c cc $(CFLAGS) -I./headers spaceship.o linkedlist.o locmath.o blast.o model.o subroutine.o keyboard.o game.c  -lm `pkg-config --libs allegro-5 allegro_primitives-5 allegro_image-5` -o game
	cc $(CFLAGS) -I./headers spaceship.o linkedlist.o locmath.o blast.o model.o subroutine.o keyboard.o game.c  -lm `pkg-config --libs allegro-5 allegro_primitives-5 allegro_image-5` -o game
clean:
	rm game
clean-all:
	rm *.o
	rm game
