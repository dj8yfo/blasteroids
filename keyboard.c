#include <keyboard.h>
#include <allegro5/allegro.h>
#include <dbg.h>
#include <linkedlist.h>
int key_flags[KEY_NUM] = {0, 0, 0, 0, 0};
int ignored_repeats[IGNORED_REPEATS] = {KEY_SPACE};
int (*key_reacts[]) (Spaceship *s, struct GameModel *model) = {rotate_ship_right, rotate_ship_left, accelerate_ship, decelerate_ship, fire_blast};
void readct_to_keys(struct GameModel *model) {
    tNode* node = get_nth(model->shipslist, 0);
    Spaceship* mains = getShip(node);
    check_mem(mains);
    al_lock_mutex(model->mutex);
    for(int i = 0; i < KEY_NUM; i++) {
        int ignored = 0;
        for(int j =0; j<IGNORED_REPEATS; j++) {
            if(i == ignored_repeats[j])
                ignored = 1;
        }
        if(ignored) {
            if(key_flags[i] == 2) {
                key_flags[i] = 0;
            } else if(key_flags[i] == 1) {
                key_reacts[i](mains, model);
                key_flags[i] = 0;
            }
        } else
        if(key_flags[i]) {
            key_reacts[i](mains, model);
        }
    }
    al_unlock_mutex(model->mutex);
error:
    return;
}

void key_switcher(int key_code, int down) {
    int index;

    switch(key_code) {
    case ALLEGRO_KEY_A:
        index = KEY_A;
        break;

    case ALLEGRO_KEY_D:
        index = KEY_D;
        break;

    case ALLEGRO_KEY_S:
        index = KEY_S;
        break;

    case ALLEGRO_KEY_W:
        index = KEY_W;
        break;
    case ALLEGRO_KEY_SPACE: {
        index = KEY_SPACE;
        break;
    }
    }
    for (int j = 0; j < IGNORED_REPEATS; j++) {
        if(index == ignored_repeats[j] && down == 2) {
            goto exit;
        }
    }

    key_flags[index] = down;
    debug("key code pressed: %d %d", key_code, down);
exit: ;
}
