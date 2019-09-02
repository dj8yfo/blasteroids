#ifndef __blast_h_
#define __blast_h_
#include <model.h>


Blast createBlast(float speed, float stx, float sty, float direction);
void step_blast(Blast* b);
void draw_blast(Blast* b, struct GameModel *model);
#endif // __blast_h_
