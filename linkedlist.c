#include <stdlib.h>
#include <dbg.h>
#include <string.h>
#include <linkedlist.h>
tNode* addNodeSpaceship(tNode** current, struct Spaceship *s) {


    Spaceship *heaps = malloc(sizeof(Spaceship));
    check_mem(heaps);
    memcpy(heaps, s, sizeof(Spaceship));
    tNode* newnode = malloc(sizeof(tNode) - 1 + sizeof(Spaceship*));
    check_mem(newnode);
    tNode stru = {.next = NULL, .prev = NULL,
                  .payload_type = PAYLOAD_SHIP};
    *newnode = stru;
    Spaceship **nodeship = (Spaceship **) &newnode->payload;
    /* log_info("pointer to be assigned to: %p", *current); */
    *nodeship = heaps;
    if(!*current) {
        (*current) = newnode;
    } else {
        tNode *last = *current;
        while(last->next) {
            last = last->next;
        }
        last->next = newnode;
        newnode->prev = last;
    }
    return newnode;
error:
    return NULL;
}

tNode* get_nth(tNode* start, int index) {
    tNode* curr = start;
    for (int i = 0; (curr != NULL && i < index); ++i) {
        curr = curr->next;
    }
    return curr;
}

Spaceship* getShip(tNode *node) {
    switch (node->payload_type) {
    case PAYLOAD_SHIP: {
        Spaceship **nodeship = (Spaceship **) &node->payload;
        return *nodeship;
    }
    default:
        return NULL;
    }
}

void freeList(tNode *node) {
    if(node->next) {
        freeList(node->next);
    }
    switch (node->payload_type) {
    case PAYLOAD_SHIP: {
        Spaceship **nodeship = (Spaceship **) &node->payload;
        free(*nodeship);
        break;
    }
default:
        break;
    }
    free(node);
}
