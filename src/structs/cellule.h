#ifndef __CELLULE_H__
#define __CELLULE_H__

#include "celmot.h"

typedef struct cellule {
    Celmot* valeur;
    struct cellule* suivant;
} Cellule, *Liste;

Liste liste_new();
void liste_add(Liste l, Liste elem);

#endif
