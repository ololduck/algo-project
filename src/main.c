#include <stdio.h>
#include <stdlib.h>

#include "parsing.h"

#define N 0xfff


static void print_tab(Cellule* tab, int tab_len) {
    int i = 0;
    for(; i< tab_len; ++i) {
        liste_print(&tab[i]);
    }
}


int main(int argc, char *argv[])
{

    Cellule tab[N];
    int i = 0;
    for(; i<N; ++i) {
        tab[i].valeur = NULL;
        tab[i].suivant = NULL;
    }
    Liste alphab = NULL;
    parse_file(tab, N, argv[1], &alphab);
    print_tab(&tab, N);
    /* liste_print(alphab); */

    return 0;
}
