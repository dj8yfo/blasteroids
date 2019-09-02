#include <spaceship.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <locmath.h>
#include <model.h>
#define NDEBUG
#include <dbg.h>
const float SPEED_INCREMENT = 0.04;
const float ROTATION_SPEED = 46;
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
    ship->speed = 0.0;
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

int accelerate_ship(Spaceship *s, struct GameModel *model) {
    s->speed += SPEED_INCREMENT;
    debug("spaceship speed : %f", s->speed);
    return 0;
}
int decelerate_ship(Spaceship *s, struct GameModel *model) {
    s->speed -= SPEED_INCREMENT;
    if(s->speed <= 0.0) {
        s->speed = 0.0;
    }
    debug("spaceship speed : %f", s->speed);
    return 0;
}

int rotate_ship_right(Spaceship *s, struct GameModel *model) {
    float sp = s->speed;
    if(sp) {
        s->heading -= ROTATION_SPEED/(sp*sp);
    }
    return 0;
}

int rotate_ship_left(Spaceship *s, struct GameModel *model) {
    float sp = s->speed;
    if(sp) {
        s->heading += ROTATION_SPEED/(sp*sp);
    }
    return 0;
}

int fire_blast(Spaceship* s, struct GameModel *model) {
    if(s->speed > 0.0) {
        Blast res = createBlast(s->speed, s->sx, s->sy, s->heading);
        tNode* inter = addNodeBlast(&model->blastlist, &res);
        check_mem(inter);
        log_info("fired blast %f %f", res.startx, res.starty);
    }
    return 0;
error:
    return -1;
}
