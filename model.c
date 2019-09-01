#include <stdlib.h>
#include <allegro5/allegro.h>
#include <model.h>
#include <spaceship.h>
#include <math.h>
#include <dbg.h>
struct GameModel* init_model(float width, float height, ALLEGRO_DISPLAY *display) {

    Spaceship *ship = malloc(sizeof(Spaceship));
    check_mem(ship);
    Spaceship *derelict = malloc(sizeof(Spaceship));
    check_mem(derelict);
    struct GameModel *res = malloc(sizeof(struct GameModel));
    check_mem(res);
    Center *cr = malloc(sizeof(Center));
    check_mem(cr);
    Center center = {.x = width/2.0, .y = height/2.0, .speed = 0.0,
                     .direction = SHIP_DISPLAY_ROT};
    *cr = center;
    *ship = create_spaceship(width/2.0, height/2.0, SHIP_DISPLAY_ROT,
                             al_map_rgb(0, 244, 0), 0.2);
    *derelict = create_spaceship(width/2.0 + 40, height/2.0 + 40, SHIP_DISPLAY_ROT,
                                 al_map_rgb(0, 244, 244), 0.0);
    ALLEGRO_MUTEX *mx = al_create_mutex();
    struct GameModel stru = {.ship = ship, .derelict = derelict, .width = width, .height = height,
                  .display = display, .mutex = mx, .cr = cr};
    log_info("init model with %f %f", width, height);
    *res = stru;
    return res;
error:
    if(ship) free(ship);
    if(derelict) free(derelict);
    if(cr) free(cr);
    return NULL;
}

void draw_model(struct GameModel *mod) {
    draw_ship(mod->derelict, mod);
    draw_ship(mod->ship, mod);
}

float screencenterx(struct GameModel *mod) {
    return mod->width/2.0;
}
float screencentery(struct GameModel *mod) {
    return mod->height/2.0;
}
float gx(struct GameModel *mod, float x) {
    return x - mod->cr->x;
}
float gy(struct GameModel *mod, float y) {
    return y - mod->cr->y;
}
void step_model(struct GameModel *mod) {
    /* step_center(mod->cr); */
    step_ship(mod->ship);
    step_ship(mod->derelict);
    /* redir_center(mod); */
}

void destr_model(struct GameModel *mod) {
    al_destroy_mutex(mod->mutex);
    free(mod->ship);
    free(mod->cr);
    free(mod);
}
