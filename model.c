#include <stdlib.h>
#include <allegro5/allegro.h>
#include "model.h"
#include "dbg.h"
Model* init_model(float width, float height, ALLEGRO_DISPLAY *display) {

    Spaceship *ship = malloc(sizeof(Spaceship));
    check_mem(ship);
    Model *res = malloc(sizeof(Model));
    check_mem(res);
    *ship = create_spaceship(width/2.0, height/2.0, 0.0);
    Model stru = {.ship = ship, .width = width, .height = height,
                  .display = display};
    log_info("init model with %f %f", width, height);
    *res = stru;
    return res;
error:
    if(ship) free(ship);
    return NULL;
}

void draw_model(Model *mod) {
    draw_ship(mod->ship, mod->display);
}

void destr_model(Model *mod) {
    free(mod->ship);
    free(mod);
}
