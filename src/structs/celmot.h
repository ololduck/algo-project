#ifndef __CELMOT_H__
#define __CELMOT_H__

#include "celpos.h"

typedef struct celmot
{
    char* mot;
    Listepos positions;
} Celmot;

Celmot* celmot_new(char* mot);
void celmot_add_position(Celmot* l, int position);
void celmot_print(Celmot* l);


/*
options is an value representing the following mask:
.......x if x is set, then this function will free the corresponding Listepos
 */
void celmot_free(Celmot* c, char options);

#endif
