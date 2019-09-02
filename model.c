#define NDEBUG
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <model.h>
#include <spaceship.h>
#include <math.h>
#include <dbg.h>
#include <linkedlist.h>
struct GameModel* init_model(float width, float height, ALLEGRO_DISPLAY *display) {

    Spaceship ship = create_spaceship(width/2.0, height/2.0, SHIP_DISPLAY_ROT,
                                      al_map_rgb(0, 244, 0), 0.0);
    Spaceship derelict = create_spaceship(width/2.0 + 40, height/2.0 + 40, SHIP_DISPLAY_ROT,
                                          al_map_rgb(0, 244, 244), 0.0);
    struct GameModel *res = malloc(sizeof(struct GameModel));
    check_mem(res);
    Center *cr = malloc(sizeof(Center));
    check_mem(cr);
    Center center = {.x = width/2.0, .y = height/2.0,
                     .dx = 0.0, .dy = 0.0};
    *cr = center;
    tNode* shiplist = NULL;
    tNode* ress;
    ress = addNodeSpaceship(&shiplist, &ship);
    check_mem(res);
    ress = addNodeSpaceship(&shiplist, &derelict);
    check_mem(res);
    ALLEGRO_MUTEX *mx = al_create_mutex();
    struct GameModel stru = {.shipslist = shiplist, .width = width, .height = height,
                  .display = display, .mutex = mx, .cr = cr};
    log_info("init model with %f %f", width, height);
    *res = stru;
    return res;
error:
    if(cr) free(cr);
    if(shiplist) freeList(shiplist);
    return NULL;
}

void draw_model(struct GameModel *mod) {
    tNode* shipnode = mod->shipslist;
    while(shipnode) {
        Spaceship *s = getShip(shipnode);
        if(s) {
            debug("drawing ship from shiplist %f %f", s->sx, s->sy);
            draw_ship(s, mod);
        }
        shipnode = shipnode->next;
    }
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

float relx(struct GameModel *mod, float x) {
    return gx(mod, x) + screencenterx(mod);
}
float rely(struct GameModel *mod, float y) {
    return gy(mod, y) + screencentery(mod);
}

void step_center(Center *cr) {
    cr->x += cr->dx;
    cr->y += cr->dy;
}

void redir_center(struct GameModel *mod) {
    tNode* main_ship_n = get_nth(mod->shipslist, 0);
    Spaceship *mains = getShip(main_ship_n);
    check_mem(mains);
    float difx = mains->sx - mod->cr->x;
    float dify = mains->sy - mod->cr->y;
    float distance = sqrtf(difx *difx  + dify *dify);
    float newnorm = 4*(distance / mod->height) * mains->speed;
    if(distance) {
        mod->cr->dx = difx/distance * newnorm;
        mod->cr->dy = dify/distance * newnorm;
    } else {
        mod->cr->dx =0;
        mod->cr->dy =0;
    }
    return;
error:
    return;
}
void step_model(struct GameModel *mod) {
    step_center(mod->cr);

    tNode* shipnode = mod->shipslist;
    while(shipnode) {
        Spaceship *s = getShip(shipnode);
        if(s) {
            debug("stepping ship from shiplist %f %f", s->sx, s->sy);
            step_ship(s);
        }
        shipnode = shipnode->next;
    }
    redir_center(mod);
}

void destr_model(struct GameModel *mod) {
    al_destroy_mutex(mod->mutex);
    freeList(mod->shipslist);
    free(mod->cr);
    free(mod);
}
