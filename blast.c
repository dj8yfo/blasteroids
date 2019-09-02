#define NDEBUG
#include <dbg.h>
#include <blast.h>
#include <locmath.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
const float BLAST_MAX_LATENCY = 25;
const float BLAST_SPEED_MUL = 4;
const float BLAST_DASHED_LEN = 10;
Blast createBlast(float speed, float stx, float sty, float direction) {
    float dir = deg_to_rad(direction);
    float blspeed = speed * BLAST_SPEED_MUL;
    float blmx = stx + blspeed * cos(dir) * BLAST_MAX_LATENCY;
    float blmy = sty + blspeed * sin(dir) * BLAST_MAX_LATENCY;
    Blast res = {.startx = stx, .starty = sty,
                 .tipx = stx, .tipy = sty, .vanished = 0,
                 .speed = blspeed, .direction = dir,
                 .blast_maxx = blmx, .blast_maxy = blmy};
    return res;
}

void step_blast(Blast* b) {
    float dir = b->direction;
    float dx = b->speed * cos(dir);
    float dy = b->speed * sin(dir);
    if(!b->vanished) {
        b->tipx += dx;
        b->tipy += dy;
    }
    float dist = sqrtf(powf((b->tipx - b->startx), 2.0) + powf((b->tipy - b->starty), 2.0));
    float distm = sqrtf(powf((b->blast_maxx - b->startx), 2.0) + powf((b->blast_maxy - b->starty), 2.0));
    float coef = dist/distm;

    if(coef >= 1.0) {
        b->vanished = 1;
        debug("finished stepping blast %f", coef);
    }
}

void draw_blast(Blast* b, struct GameModel *model) {
    //
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform);
    ALLEGRO_DISPLAY *display = model->display;
    al_translate_transform(&transform, relx(model, 0), rely(model, 0));
    al_set_target_backbuffer(display);
    al_use_transform(&transform);
    float tipx = b->startx, tipy = b->starty;
    int parity = 0;
    float dist = sqrtf(powf((tipx - b->startx), 2.0) + powf((tipy - b->starty), 2.0));
    float distm = sqrtf(powf((b->tipx - b->startx), 2.0) + powf((b->tipy - b->starty), 2.0));
    float coef = dist/distm;
    while( coef < 1.0) {
        debug("drawing blast sector: %f tipx %f coef %f", tipx, b->blast_maxx, coef);
        float tipx1 = tipx + BLAST_DASHED_LEN * cos(b->direction);
        float tipy1 = tipy + BLAST_DASHED_LEN * sin(b->direction);
        if(parity % 2 == 0) {
            al_draw_line(tipx, tipy, tipx1, tipy1, al_map_rgb(255, 243, 0), 2.0f);
        }
        tipx = tipx1;
        tipy = tipy1;
        parity++;
        dist = sqrtf(powf((tipx - b->startx), 2.0) + powf((tipy - b->starty), 2.0));
        distm = sqrtf(powf((b->tipx - b->startx), 2.0) + powf((b->tipy - b->starty), 2.0));
        coef = dist/distm;
    }
    /* log_info("finished drawing blast"); */
}
