#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "dbg.h"
#include "game.h"
#include "model.h"
#include "spaceship.h"

const float FPS = 60;
const int DISP_WIDTH = 1600;
const int DISP_HEIGHT = 900;

int main(int argc, char **argv){

   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   bool redraw = true;

   int rc = alle_comps_init(&display, &timer, &event_queue);
   check(rc == 0, "Failed to init one of allegrocomps");
   Model *gameint = init_model(DISP_WIDTH, DISP_HEIGHT, display);
   check_mem(gameint);

   al_clear_to_color(al_map_rgb(0,0,0));
   al_flip_display();
   al_start_timer(timer);


   while(1)
   {
       ALLEGRO_EVENT ev;
       al_wait_for_event(event_queue, &ev);

   mainswitch:
       switch (ev.type) {
       case ALLEGRO_EVENT_TIMER: {
           redraw = true;
           break;
       }
       case ALLEGRO_EVENT_DISPLAY_CLOSE: {
           goto exitmaineventloop;
           break;
       }
       default:
           log_err("fell into `deault' branch of `mainswitch'");
           break;
       }

       if(redraw && al_is_event_queue_empty(event_queue)) {
           redraw = false;
           al_clear_to_color(al_map_rgb(0,0,0));
           /* drawModel(gameint); */
           draw_ship(gameint->ship, display);
           al_flip_display();
       }
   }
exitmaineventloop:
   alle_cleanup(display, timer, event_queue);
   if(gameint) destr_model(gameint);
   return 0;
error:
   alle_cleanup(display, timer, event_queue);
   if(gameint) destr_model(gameint);
   return 1;
}

int alle_comps_init(ALLEGRO_DISPLAY **display,
                    ALLEGRO_TIMER **timer,
                    ALLEGRO_EVENT_QUEUE **queue) {
    check(al_init(), "failed to initialize al_init\n");
    check(al_init_primitives_addon(),
          "failed to initialize allegro primitives adon!\n");
    *timer = al_create_timer(1.0 / FPS);
    check(*timer, "failed to create timer!\n");

    *display = al_create_display(DISP_WIDTH, DISP_HEIGHT);
    check(*display, "failed to create display!\n");

    *queue = al_create_event_queue();
    check(*queue, "failed to create event_queue!\n");

    al_register_event_source(*queue, al_get_display_event_source(*display));
    al_register_event_source(*queue, al_get_timer_event_source(*timer));

    return 0;
error:
    if(*timer) al_destroy_timer(*timer);
    if(*display) al_destroy_display(*display);
    return -1;
}

void alle_cleanup(ALLEGRO_DISPLAY *display,
                  ALLEGRO_TIMER *timer,
                  ALLEGRO_EVENT_QUEUE *queue) {
    if(timer) al_destroy_timer(timer);
    if(display) al_destroy_display(display);
    if(queue) al_destroy_event_queue(queue);
}
