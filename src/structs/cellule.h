#ifndef __CELLULE_H__
#define __CELLULE_H__

#include "celmot.h"

typedef struct cellule {
    Celmot* valeur;
    struct cellule* suivant;
} Cellule, *Liste;

Liste liste_new();
void liste_add(Liste *l, Liste elem);
int liste_add_alphabetical(Liste* l, Celmot* elem);

/**
 * options is a byte which contains the options for the memfree.
 * .... ...x if x is set, we will delete the listepos contained within the celmot within the given Liste. Useless if the bit 1 is not set.
 * .... ..x. if x is set, we will free the celmot in the given Liste
 */
void liste_free(Liste l, char options);

void liste_print(Liste l);

#endif
