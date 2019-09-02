#ifndef __spaceship_
#define __spaceship_
#include <allegro5/allegro.h>
#include <allegro5/color.h>
#include <model.h>
#define SHIP_DISPLAY_ROT -90.0f
typedef struct Spaceship{
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

Spaceship create_spaceship(float initx, float inity, float rotation,
                           ALLEGRO_COLOR color, float speed) ;
int reinit_spaceshit(Spaceship *ship);
void draw_ship(Spaceship* s, struct GameModel *model);
void step_ship(Spaceship* s);
void decelerate_ship(Spaceship *s);
void accelerate_ship(Spaceship *s);
void rotate_ship_left(Spaceship *s);
void rotate_ship_right(Spaceship *s);


#endif
