#ifndef __spaceship_
#define __spaceship_
#include <allegro5/allegro.h>
#include <allegro5/color.h>
#include <center.h>
#define SHIP_DISPLAY_ROT -90.0f

typedef struct Blast{
    float startx;
    float starty;
    float speed;
    float direction; //radian
    float blast_maxx;
    float blast_maxy;
    float tipx;
    float tipy;
    int vanished;
} Blast;

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

struct GameModel {
    float width;
    float height;
    struct _tNode *shipslist;
    struct _tNode *blastlist;
    Center *cr;
    ALLEGRO_DISPLAY *display;
    ALLEGRO_MUTEX *mutex;
};
Spaceship create_spaceship(float initx, float inity, float rotation,
                           ALLEGRO_COLOR color, float speed) ;
int reinit_spaceshit(Spaceship *ship);
void draw_ship(Spaceship* s, struct GameModel *model);
int fire_blast(Spaceship* s, struct GameModel *model);
void step_ship(Spaceship* s);
int decelerate_ship(Spaceship *s, struct GameModel *model);
int accelerate_ship(Spaceship *s, struct GameModel *model);
int rotate_ship_left(Spaceship *s, struct GameModel *model);
int rotate_ship_right(Spaceship *s, struct GameModel *model);


#endif
