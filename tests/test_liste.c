/**
 * test file for the Liste struct
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "../src/structs/cellule.h"

int main(int argc, char const *argv[])
{

    // first part: we check if regular order works

    Liste l = NULL;
    assert(l==NULL);
    Celmot* mot = celmot_new("aab");
    liste_add_alphabetical(&l, mot);
    liste_print(l);
    printf("\n");
    assert(l != NULL);
    assert(l->suivant == NULL);
    assert(l->valeur == mot);
    assert(strcmp(l->valeur->mot, "aab") == 0);

    Celmot* mot2 = celmot_new("aad");
    liste_add_alphabetical(&l, mot2);
    liste_print(l);
    printf("\n");
    assert(l->valeur != mot2);
    assert(l->valeur == mot);
    assert(l->suivant != NULL);
    assert(l->suivant->valeur == mot2);

    Celmot* mot3 = celmot_new("aaa");
    liste_add_alphabetical(&l, mot3);
    liste_print(l);
    printf("\n");
    assert(l->valeur == mot3);
    assert(l->suivant->valeur == mot);

    Celmot* mot4 = celmot_new("aac");
    liste_add_alphabetical(&l ,mot4);
    liste_print(l);
    printf("\n");
    assert(l->suivant->suivant->valeur == mot4);

    liste_add_alphabetical(&l, mot3);
    liste_print(l);
    printf("\n");
    assert(l->valeur == mot3);
    assert(l->suivant->valeur == mot);



    return 0;
}


