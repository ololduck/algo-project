#include <stdio.h>
#include <stdlib.h>

#include "parsing.h"

#define N 0xffff



int main(int argc, char *argv[])
{

    Cellule tab[N];
    Liste alphab = NULL;
    parse_file(tab, N, argv[1], &alphab);
    liste_print(alphab);

    return 0;
}
