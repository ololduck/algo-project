#include "cellule.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Liste liste_new() {
    Liste l = malloc(sizeof(Cellule));
    if(l != NULL) {
        l->valeur = NULL;
        l->suivant = NULL;
    }
    return l;
}

void liste_add(Liste *l, Liste elem) {
    if(*l == NULL) {
        *l = liste_new();
        (*l)->suivant = elem;
        return ;
    }
    while(*l){
        *l = (*l)->suivant;
    }
    (*l)->suivant = elem;
}

int liste_add_alphabetical(Liste* l, Celmot* elem) {
    Liste e = *l;
    if(elem == NULL)
        return 0;
    if(*l == NULL || (*l)->valeur == NULL) {
        *l = liste_new();
        (*l)->valeur = elem;
        return 1;
    }

    if(strcmp(e->valeur->mot, elem->mot) > 0) {
        Liste to_add = liste_new();
        to_add->valeur = elem;
        to_add->suivant = e;
        *l = to_add;
        return 1;
    }
    Liste prec = e;
    e = e->suivant;

    while(e != NULL && strcmp(e->valeur->mot, elem->mot) < 0) {
        prec = e;
        e = e->suivant;
    }

    Liste to_add = liste_new();
    to_add->valeur = elem;
    to_add->suivant = e;
    prec->suivant = to_add;
    return 1;
}

void liste_print(Liste l) {
    printf("Liste: {\n");
    while(l) {
        printf("\t");
        printf("{\n\t\taddress: %x,\n\t\tvaleur: {\n", (unsigned int) l);
        printf("\t\t\t");
        celmot_print(l->valeur);
        printf("\t\t}\n\t},\n");
        l = l->suivant;
    }
    printf("}");
}

