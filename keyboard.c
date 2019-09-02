#include <keyboard.h>
#include <allegro5/allegro.h>
#include <dbg.h>
int key_flags[KEY_NUM] = {0, 0, 0, 0};
void (*key_reacts[]) (Spaceship *s) = {rotate_ship_right, rotate_ship_left, accelerate_ship, decelerate_ship};
void readct_to_keys(struct GameModel *model) {
    al_lock_mutex(model->mutex);
    for(int i = 0; i < KEY_NUM; i++) {
        if(key_flags[i])
            key_reacts[i](model->ship);
    }
    al_unlock_mutex(model->mutex);
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
    }
}
