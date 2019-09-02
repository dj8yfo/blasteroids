#include <keyboard.h>
#include <allegro5/allegro.h>
#include <dbg.h>
#include <linkedlist.h>
int key_flags[KEY_NUM] = {0, 0, 0, 0, 0};
int (*key_reacts[]) (Spaceship *s, struct GameModel *model) = {rotate_ship_right, rotate_ship_left, accelerate_ship, decelerate_ship, fire_blast};
void readct_to_keys(struct GameModel *model) {
    tNode* node = get_nth(model->shipslist, 0);
    Spaceship* mains = getShip(node);
    check_mem(mains);
    al_lock_mutex(model->mutex);
    for(int i = 0; i < KEY_NUM; i++) {
        if(key_flags[i]) {
            key_reacts[i](mains, model);
        }
    }
    al_unlock_mutex(model->mutex);
error:
    return;
}

void key_switcher(int key_code, int down) {
    debug("key code pressed: %d %s", key_code, down ? "down":"up");
    switch(key_code) {
    case ALLEGRO_KEY_A:
        key_flags[KEY_A] = down;
        break;

    case ALLEGRO_KEY_D:
        key_flags[KEY_D] = down;
        break;

    case ALLEGRO_KEY_S:
        key_flags[KEY_S] = down;
        break;

    case ALLEGRO_KEY_W:
        key_flags[KEY_W] = down;
        break;
    case ALLEGRO_KEY_SPACE: {
        key_flags[KEY_SPACE] = down;
        break;
    }
    }
}
