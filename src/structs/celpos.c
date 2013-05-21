#include "celpos.h"
#include <stdlib.h>


Listepos listepos_new(int pos) {
    Listepos p = malloc(sizeof(Celpos));
    if(p) {
        p->position = pos;
    }
    return p;
}


void listepos_add(Listepos l, Listepos elem) {
    while(l)
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