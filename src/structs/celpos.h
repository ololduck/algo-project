#ifndef __CELPOS_H__
#define __CELPOS_H__

typedef struct celpos
{
    int position;
    struct celpos* suivant;
}Celpos, *Listepos;


Listepos listepos_new(int pos);
void listepos_add(Listepos l, Listepos elem);
int listepos_appartient(Listepos l, int x);

void listepos_free(Listepos l);


#endif
