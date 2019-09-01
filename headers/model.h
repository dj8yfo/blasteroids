#ifndef __model_h_
#define __model_h_

#include <allegro5/allegro.h>
#include <spaceship.h>
#include <center.h>


struct GameModel {
    float width;
    float height;
    struct Spaceship *ship;
    struct Spaceship *derelict;
    Center *cr;
    ALLEGRO_DISPLAY *display;
    ALLEGRO_MUTEX *mutex;
};

struct GameModel* init_model(float width, float height, ALLEGRO_DISPLAY *display) ;
void draw_model(struct GameModel *mod);
void destr_model(struct GameModel *mod);
void step_center(Center *cr);
void step_model(struct GameModel *mod);
float relx(struct GameModel *mod, float x);
float rely(struct GameModel *mod, float y);

#endif // MACRO
