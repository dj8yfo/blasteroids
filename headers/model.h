#ifndef __model_h_
#define __model_h_

#include <allegro5/allegro.h>
#include <spaceship.h>
typedef struct GameModel {
    float width;
    float height;
    Spaceship *ship;
    ALLEGRO_DISPLAY *display;
    ALLEGRO_MUTEX *mutex;
} Model;

Model* init_model(float width, float height, ALLEGRO_DISPLAY *display) ;
void draw_model(Model *mod);
void destr_model(Model *mod);
void step_model(Model *mod);

#endif // MACRO
