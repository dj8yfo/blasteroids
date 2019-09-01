#include <spaceship.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <locmath.h>
#include <model.h>
#include <math.h>
#define NDEBUG
#include <dbg.h>
Spaceship create_spaceship(float initx, float inity, float rotation,
                           ALLEGRO_COLOR color, float speed) {
    log_info("init spaceship at %f %f", initx, inity);
    Spaceship res = {.startx = initx, .starty = inity,
                     .sx=initx, .sy = inity,
                     .heading = rotation,
                     .speed = speed,
                     .lives_left = 3, .interactable = 0,
                     .color = color
    };
    return res;
}

int reinit_spaceshit(Spaceship *ship) {
    ship->lives_left -= 1;
    if(ship->lives_left <=0 ) return 0;
    ship->interactable = 0;
    ship->sx = ship->startx;
    ship->sy = ship->starty;
    return 1;
}
void step_ship(Spaceship* s) {
    float dir = deg_to_rad(s->heading);
    float dx = s->speed * cos(dir);
    float dy = s->speed * sin(dir);
    s->sx += dx;
    s->sy += dy;
}

void draw_ship(Spaceship* s, struct GameModel *model)
{
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    ALLEGRO_DISPLAY *display = model->display;

    al_rotate_transform(&transform, deg_to_rad(s->heading - SHIP_DISPLAY_ROT));
    float newx = relx(model, s->sx);
    float newy = rely(model, s->sy);
    al_translate_transform(&transform, newx, newy);
    al_set_target_backbuffer(display);
    al_use_transform(&transform);
    al_draw_line(-8, 9, 0, -11, s->color, 3.0f);
    al_draw_line(0, -11, 8, 9, s->color, 3.0f);
    al_draw_line(-6, 4, -1, 4, s->color, 3.0f);
    al_draw_line(6, 4, 1, 4, s->color, 3.0f);
}
