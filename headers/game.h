int alle_comps_init(ALLEGRO_DISPLAY **display,
                    ALLEGRO_TIMER **timer_redraw,
                    ALLEGRO_TIMER **timer_keyboard,
                    ALLEGRO_EVENT_QUEUE **queue);
void alle_cleanup(ALLEGRO_DISPLAY *display,
                  ALLEGRO_TIMER *timer_redraw,
                  ALLEGRO_TIMER *timer_keyboard,
                  ALLEGRO_EVENT_QUEUE *queue);
