CFLAGS=-g -Wall
all: game
%: %.c
	gcc $^ `pkg-config --libs allegro-5 allegro_primitives-5 allegro_image-5` -o $@
game: game.c spaceship.c locmath.c model.c
	gcc game.c spaceship.c locmath.c model.c `pkg-config --libs allegro-5 allegro_primitives-5 allegro_image-5` -o game
clean:
	rm game
