#include <allegro5/allegro.h>
#include "spaceship.h"
typedef struct GameModel {
    float width;
    float height;
    Spaceship *ship;
    ALLEGRO_DISPLAY *display;
} Model;

Model* init_model(float width, float height, ALLEGRO_DISPLAY *display) ;
void draw_model(Model *mod);
void destr_model(Model *mod);
