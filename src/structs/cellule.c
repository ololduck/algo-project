#include "cellule.h"

#include <stdlib.h>

Liste liste_new() {
    Liste l = malloc(sizeof(Cellule));
    return l;
}

void liste_add(Liste l, Liste elem) {
    while(l)
        l = l->suivant;
    l->suivant = elem;
}
