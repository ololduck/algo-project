#include "celpos.h"
#include <stdlib.h>


Listepos listepos_new(int pos) {
    Listepos p = malloc(sizeof(Celpos));
    if(p) {
        p->position = pos;
        p->suivant = NULL;
    }
    return p;
}


void listepos_add(Listepos l, Listepos elem) {
    if(!l)
        return;
    while(l->suivant)
        l = l->suivant;
    l->suivant = elem;
}


int listepos_appartient(Listepos l, int x) {
    while(l) {
        if(l->position == x)
            return 1;
        l = l->suivant;
    }
    return 0;
}

void listepos_free(Listepos l) {
    if(l != NULL) {
        if(l->suivant != NULL)
            listepos_free(l->suivant);
        l->suivant = NULL;
        free(l);
    }
}
