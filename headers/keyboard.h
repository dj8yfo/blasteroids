#include <model.h>
#include <spaceship.h>
#define KEY_NUM 4
enum MYKEYS {
    KEY_A, KEY_D, KEY_W, KEY_S
};
extern void (*key_reacts[]) (Spaceship *s);
void readct_to_keys(struct GameModel *model);
void key_switcher(int key_code, int down);
