#include <subroutine.h>
#include <model.h>
#include <dbg.h>
void *model_modification_routine(ALLEGRO_THREAD *thr, void *modelarg) {
    struct GameModel *model = (struct GameModel *) modelarg;

    al_rest(1);
    while(!al_get_thread_should_stop(thr)){

        al_lock_mutex(model->mutex);
        step_model(model);
        al_unlock_mutex(model->mutex);

        al_rest(1 / MODEL_FREQUENCY);
    }
    log_info("model thread finished: success");
    return model;
}
