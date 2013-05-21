#include "celmot.h"

#include <stdlib.h>
#include <string.h>

Celmot* celmot_new(char* mot) {
    Celmot* m = malloc(sizeof(Celmot));
    if(m)
        m->mot = mot;
    return m;
}

void celmot_add(Celmot* l, Celmot* elem) {
    Celmot* prec = l;
    while(l) {
        /* utiliser strcmp */
        if(strcmp(l->mot, elem->mot) > -1 && strcmp(elem->mot, prec->mot) < 1) {
            /* effectuer la liaison avec le reste de la chaine. */
            prec->suivant = elem;
            elem->suivant = l;
            return;
        }
        prec = l;
        l = l->suivant;
    }
}

