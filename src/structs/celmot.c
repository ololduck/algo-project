#include "celmot.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Celmot* celmot_new(char* mot) {
    Celmot* m = malloc(sizeof(Celmot));
    if(m) {
        m->mot = mot;
        m->positions = NULL;
    }
    return m;
}

void celmot_add_position(Celmot* l, int position) {
    Listepos pos = l->positions;
    if(pos == NULL) {
        l->positions = listepos_new(position);
        return;
    }

    while(pos->suivant != NULL){
        pos = pos->suivant;
    }
    pos->suivant = listepos_new(position);
}

void celmot_print(Celmot* l) {
    if(l == NULL || l->mot == NULL) {
        return;
    }
    printf("celmot { addresse: %x, mot: %s, positions: ", (unsigned int)l, l->mot);
    Listepos pos = l->positions;
    while(pos) {
        printf("%d, ", pos->position);
        pos = pos->suivant;
    }
    printf("}\n");
}

void celmot_free(Celmot* c, char options) {
    if(c != NULL) {
        if(options & 1)
            listepos_free(c->positions);
        if(c->mot != NULL)
            free(c->mot);
        c->positions = NULL;
        c->mot = NULL;
        free(c);
    }
}
