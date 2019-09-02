#ifndef __linkedlist_h_
#define __linkedlist_h_

#include <spaceship.h>
#include <blast.h>
typedef struct _tNode {
    struct _tNode *prev;
    struct _tNode *next;
    int payload_type;
    char payload;
} tNode;

typedef enum {
    PAYLOAD_SHIP, PAYLOAD_BLAST
} tPayLoad;
tNode* addNodeSpaceship(tNode** current, struct Spaceship *s);
tNode* addNodeBlast(tNode** current, struct Blast *s);
tNode* get_nth(tNode* start, int index);
struct Spaceship* getShip(tNode *node);
struct Blast* getBlast(tNode *node);
void freeList(tNode *node);
#endif // __linkedlist_h_
