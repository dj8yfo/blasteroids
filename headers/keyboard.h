#include <model.h>
#include <spaceship.h>
#define KEY_NUM 5
#define IGNORED_REPEATS 1
enum MYKEYS {
    KEY_A, KEY_D, KEY_W, KEY_S, KEY_SPACE
};
extern int (*key_reacts[]) (Spaceship *s, struct GameModel *model);
void readct_to_keys(struct GameModel *model);
void key_switcher(int key_code, int down);
