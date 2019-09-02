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

void freePayload(tNode *node) {
    
    switch (node->payload_type) {
    case PAYLOAD_SHIP: {
        Spaceship **nodeship = (Spaceship **) &node->payload;
        free(*nodeship);
        break;
    }
    case PAYLOAD_BLAST: {
        Blast **nodeblast = (Blast **) &node->payload;
        free(*nodeblast);
        break;
    }
    default:
        break;
    }
}

tNode* removeNode(tNode** start, tNode* interm) {
    tNode* res = interm->next;
    if(interm == NULL) return NULL;
    if(interm->prev == NULL && interm == *start) {
        if(interm->next == NULL) {
            *start = NULL;
            freePayload(interm);
            free(interm);
        } else {
            *start = interm->next;
            interm->next->prev = interm->prev;
            freePayload(interm);
            free(interm);
        }
    } else if (interm->prev != NULL){
        log_info("pointer modification 2");
        interm->prev->next = interm->next;
        if(interm->next) {
            interm->next->prev = interm->prev;
        }
        freePayload(interm);
        free(interm);
    } else {
        sentinel("unreachable removeNOde %p (interm) %p (*start)", interm, *start);
    }
    return res;
error:
    return NULL;
}

tNode* addNodeBlast(tNode** current, struct Blast *s) {


    Blast *heaps = malloc(sizeof(Blast));
    check_mem(heaps);
    memcpy(heaps, s, sizeof(Blast));
    tNode* newnode = malloc(sizeof(tNode) - 1 + sizeof(Blast*));
    check_mem(newnode);
    tNode stru = {.next = NULL, .prev = NULL,
                  .payload_type = PAYLOAD_BLAST};
    *newnode = stru;
    Blast **nodeship = (Blast **) &newnode->payload;
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

Blast* getBlast(tNode *node) {
    switch (node->payload_type) {
    case PAYLOAD_BLAST: {
        Blast **nodeship = (Blast **) &node->payload;
        return *nodeship;
    }
    default:
        return NULL;
    }
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
    freePayload(node);
    free(node);
}


