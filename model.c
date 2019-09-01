#include <stdlib.h>
#include <allegro5/allegro.h>
#include <model.h>
#include <spaceship.h>
#include <math.h>
#include <dbg.h>
Model* init_model(float width, float height, ALLEGRO_DISPLAY *display) {

    Spaceship *ship = malloc(sizeof(Spaceship));
    check_mem(ship);
    Model *res = malloc(sizeof(Model));
    check_mem(res);
    *ship = create_spaceship(width/2.0, height/2.0, SHIP_DISPLAY_ROT);
    ALLEGRO_MUTEX *mx = al_create_mutex();
    Model stru = {.ship = ship, .width = width, .height = height,
                  .display = display, .mutex = mx};
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

void step_model(Model *mod) {
    step_ship(mod->ship);
}

void destr_model(Model *mod) {
    al_destroy_mutex(mod->mutex);
    free(mod->ship);
    free(mod);
}
