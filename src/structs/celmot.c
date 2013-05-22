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
        pos = listepos_new(position);
        return;
    }

    while(pos->suivant != NULL){
        pos = pos->suivant;
    }
    pos->suivant = listepos_new(position);
}

void celmot_print(Celmot* l) {
    printf("celmot { addresse: %x, mot: %s, positions: ", l, l->mot);
    Listepos pos = l->positions;
    while(pos) {
        printf("%d, ", pos->position);
        pos = pos->suivant;
    }
    printf("}\n");
}
