#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <dbg.h>
#include <game.h>
#include <model.h>
#include <spaceship.h>
#include <subroutine.h>
#include <keyboard.h>


const float FPS = 60;
const int DISP_WIDTH = 1600;
const int DISP_HEIGHT = 900;

int main(int argc, char **argv){

    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_THREAD *model_routine = NULL;
    bool redraw = true;

    int rc = alle_comps_init(&display, &timer, &event_queue);
    struct GameModel *gameint = init_model(DISP_WIDTH, DISP_HEIGHT, display);
    check(rc == 0, "Failed to init one of allegrocomps");
    check_mem(gameint);
    model_routine = al_create_thread(model_modification_routine, gameint);
    check_mem(model_routine);
    al_start_thread(model_routine);

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
            readct_to_keys(gameint);
            redraw = true;
            break;
        }
        case ALLEGRO_EVENT_DISPLAY_CLOSE: {
            goto exitmaineventloop;
            break;
        }
        case ALLEGRO_EVENT_KEY_DOWN:
        case ALLEGRO_EVENT_KEY_CHAR:
        {
            key_switcher(ev.keyboard.keycode, 1);
            break;
        }
        case ALLEGRO_EVENT_KEY_UP: {
            key_switcher(ev.keyboard.keycode, 0);
            break;
        }
        default:
            log_err("fell into `deault' branch of `mainswitch'");
            break;
        }

        if(redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(0,0,0));
            al_lock_mutex(gameint->mutex);
            draw_model(gameint);
            al_unlock_mutex(gameint->mutex);

            al_flip_display();
        }
    }
exitmaineventloop:
    al_destroy_thread(model_routine);
    alle_cleanup(display, timer, event_queue);
    al_uninstall_keyboard();
    if(gameint) destr_model(gameint);
    return 0;
error:
    al_destroy_thread(model_routine);
    alle_cleanup(display, timer, event_queue);
    al_uninstall_keyboard();
    if(model_routine) al_destroy_thread(model_routine);
    if(gameint) destr_model(gameint);
    return 1;
}

int alle_comps_init(ALLEGRO_DISPLAY **display,
                    ALLEGRO_TIMER **timer,
                    ALLEGRO_EVENT_QUEUE **queue) {
    check(al_init(), "failed to initialize al_init\n");
    check(al_init_primitives_addon(),
          "failed to initialize allegro primitives adon!\n");
    check(al_install_keyboard(),
          "failed to initialize the keyboard!\n");

    *timer = al_create_timer(1.0 / FPS);
    check(*timer, "failed to create timer!\n");

    *display = al_create_display(DISP_WIDTH, DISP_HEIGHT);
    check(*display, "failed to create display!\n");

    *queue = al_create_event_queue();
    check(*queue, "failed to create event_queue!\n");

    al_register_event_source(*queue, al_get_display_event_source(*display));
    al_register_event_source(*queue, al_get_timer_event_source(*timer));
    al_register_event_source(*queue, al_get_keyboard_event_source());

    return 0;
error:
    if(*timer) al_destroy_timer(*timer);
    if(*display) al_destroy_display(*display);
    return -1;
}

void alle_cleanup(ALLEGRO_DISPLAY *display,
                  ALLEGRO_TIMER *timer,
                  ALLEGRO_EVENT_QUEUE *queue) {
    if(timer) {
        al_destroy_timer(timer);
        log_info("destroyed timer");
    }
    if(display) {al_destroy_display(display);
        log_info("destroyed display");
    }
    if(queue) {
        al_destroy_event_queue(queue);
        log_info("destroyed event queue");
    }
}
