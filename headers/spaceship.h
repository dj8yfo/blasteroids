#ifndef __spaceship_
#define __spaceship_
#include <allegro5/allegro.h>
#include <allegro5/color.h>
#define SHIP_DISPLAY_ROT -90.0f
typedef struct {
    float sx;
    float sy;
    float startx;
    float starty;
    float heading;
    float speed;
    int lives_left;
    int interactable;
    ALLEGRO_COLOR color;
} Spaceship;

Spaceship create_spaceship(float initx, float inity, float rotation) ;
int reinit_spaceshit(Spaceship *ship);
void draw_ship(Spaceship* s, ALLEGRO_DISPLAY* display);
void step_ship(Spaceship* s);
#endif
