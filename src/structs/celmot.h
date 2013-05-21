#ifndef __CELMOT_H__
#define __CELMOT_H__

#include "celpos.h"

typedef struct celmot
{
    char* mot;
    Listepos positions;
} Celmot;

Celmot* celmot_new(char* mot);
void celmot_add(Celmot* l, Celmot* elem);

#endif
