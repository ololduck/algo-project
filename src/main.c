#include <stdio.h>
#include <stdlib.h>

#include "parsing.h"
#include "wordqueries.h"

#define N 0x8f


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
    printf("hello\n");
    printf("after in tab: %d\n", belongs("after", tab, N));
    print_positions("a", tab, N);
    print_sentences_containing_word("a", argv[1], tab, N);
    print_alphabetical(alphab);
    print_all_from_prefix("so", alphab);

    for(i = 0; i<N; ++i)
        liste_free(tab[i].suivant, 0x3);
    liste_free(alphab, 0x0);

    return 0;
}
