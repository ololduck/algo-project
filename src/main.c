#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "parsing.h"
#include "wordqueries.h"

#define N 0xf


static void print_tab(Cellule* tab, int tab_len) {
    int i = 0;
    for(; i< tab_len; ++i) {
        liste_print(&tab[i]);
    }
}

static void print_help() {
    printf("Index v1.0.1\n"
"Usage: Index [-h] [-apPldD] FILE\n"
"\t-a\t--appartient\tMOT\t Teste la présence de MOT dans FILE\n"
"\t-p\t--positions\tMOT\tAffiche les positions de MOT, si présent dans FILE\n"
"\t-P\t--phrases\tMOT\tAffiche les phrases contenant MOT dans FILE\n"
"\t-l\t--liste\tAffiche la liste des mots présents FILE, alphabetiquement\n"
"\t-d\t--prefixe\tPREFIX\tAffiche la liste des mots présents dans FILE dont PREFIXE est le prefixe.\n"
"\t-D\t--tofile\tOUTFILE\tSauvegarde la liste des mots dans OUTFILE.DICO\n"
"\n");
}


int main(int argc, char *argv[])
{

    const char* optstring = ":ha:p:P:ld:D:";
    const struct option lopts[] = {
        {"help", no_argument, NULL, 'h'},
        {"appartient", required_argument, NULL, 'a'},
        {"positions", required_argument, NULL, 'p'},
        {"phrases", required_argument, NULL, 'P'},
        {"liste", no_argument, NULL, 'l'},
        {"prefixe", required_argument, NULL, 'd'},
        {"tofile", required_argument, NULL, 'D'},
        {NULL, no_argument, NULL, 0}
    };

    int val,index=-1;
    int last_val = val;
    char* last_optarg;


    while (EOF!=(val=getopt_long(argc,argv,optstring,lopts,&index))) {
        char msg[32];
        if (index==-1) sprintf(msg,"short option -%c",val);
        else sprintf(msg,"long option --%s",lopts[index].name);

        if(val == 'h') {
            print_help();
            exit(0);
        }
        last_val = val;
        last_optarg = optarg;
        #ifdef DEBUG
        printf("Option %c with opt %s recieved\n", val, optarg);
        #endif
        index=-1;
    }

    Cellule tab[N];
    int i = 0;
    for(; i<N; ++i) {
        tab[i].valeur = NULL;
        tab[i].suivant = NULL;
    }
    Liste alphab = NULL;

    if(optind < argc) {
        parse_file(tab, N, argv[optind], &alphab);
        if(last_val == 'a') {
            int res = belongs(last_optarg, tab, N);
            if(res)
                printf("Word %s is in file %s",last_optarg, argv[optind]);
            else
                printf("Word %s is not in file %s", last_optarg, argv[optind]);
        }
        else if(last_val == 'p') {
            print_positions(last_optarg, tab, N);
        }
        else if(last_val == 'P') {
            print_sentences_containing_word(last_optarg, argv[optind], tab, N);
        }
        else if(last_val == 'l') {
            print_alphabetical(alphab);
        }
        else if(last_val =='d') {
            print_all_from_prefix(last_optarg, alphab);
        }
        else if(last_val == 'D') {
            save_positions_to_file(last_optarg, alphab);
        }
    }
    else {
        fprintf(stderr, "Error: not enough arguments\n");
        print_help();
    }


    #ifdef DEBUG
    print_tab(tab, N);
    #endif


    for(i = 0; i<N; ++i)
        liste_free(tab[i].suivant, 0x3);
    liste_free(alphab, 0x0);

    return 0;
}
