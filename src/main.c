#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "parsing.h"
#include "wordqueries.h"

#define N 0x8f

static const char* version = "1.0.3";


static void print_tab(Cellule* tab, int tab_len) {
    int i = 0;
    for(; i< tab_len; ++i) {
        liste_print(&tab[i]);
    }
}

static void interactive_menu(Cellule* tab, int tab_len, Liste* alphab) {
    /* TODO */
    char choice = 0;
    char fname[256];
    char mot[32];
    printf("Index v%s - Menu interactif\n\n", version);
    printf("Entrez le nom du fichier à analyser: ");
    scanf("%s", fname);
    getchar(); /* removes the \n */
    FILE* tmp;
    if((tmp = fopen(fname, "r")) == NULL) {
        fprintf(stderr, "Error: file %s cannot be found.", fname);
        exit(1);
    }
    fclose(tmp);

    parse_file(tab, tab_len, fname, alphab);
    while(choice != 'q' && choice != EOF) {
        printf("Choix\n"
            "\n"
            "a - teste l'appartenance d'un mot au fichier\n"
            "p - affiche les positions de mot dans le fichier\n"
            "P - affiche les phrases contenant mot dans le fichier\n"
            "l - affiche l'intégralité ddes mots (triés) présents dans le texte\n"
            "d - affiche l'ensemble des mots du texte ayant pour préfixe mot\n"
            "D - sauvegarde dans un fichier la liste des mots, avec leurs positions\n"
            "q ou ctrl+d - quitter\n"
            "\n"
            "Que voulez vous faire?\n"
            );
        choice = getchar();
        if(choice != EOF)
            getchar(); /* removes the \n */
        #ifdef DEBUG
        printf("Choice: %c (%d)", choice, choice);
        #endif
        if(choice == 'a'){
            printf("Entrez le mot à rechercher: ");
            scanf("%s", mot);
            getchar(); /* removes the \n */
            if(belongs(mot, tab, tab_len)) {
                printf("%s appartient à %s\n", mot, fname);
            }
            else
                printf("%s n'appartient pas à %s\n", mot, fname);
        }
        else if(choice == 'p') {
            printf("Entrez le mot à rechercher: ");
            scanf("%s", mot);
            getchar(); /* removes the \n */
            print_positions(mot, tab, tab_len);
        }
        else if(choice == 'P') {
            printf("Entrez le mot à rechercher: ");
            scanf("%s", mot);
            getchar(); /* removes the \n */
            print_sentences_containing_word(mot, fname, tab, tab_len);
        }
        else if(choice == 'l') {
            print_alphabetical(*alphab);
        }
        else if(choice =='d') {
            printf("Entrez le mot à rechercher: ");
            scanf("%s", mot);
            getchar(); /* removes the \n */
            print_all_from_prefix(mot, *alphab);
        }
        else if(choice == 'D') {
            char fsave[256];
            printf("Entrez le nom de fichier dans lequel sauvegarder: ");
            scanf("%s", fsave);
            getchar(); /* removes the \n */
            save_positions_to_file(fsave, *alphab);
        }
        else if(choice == 'q' || choice == EOF) {
            printf("Quit.\n");
        }
        else
            printf("Not a valid choice: %c\n", choice);

    }

}

static void print_help() {
    printf("Index v%s\n"
"Usage: Index [-h] [-apPldD] FILE\n"
"\t-a\t--appartient\tMOT\t Teste la présence de MOT dans FILE\n"
"\t-p\t--positions\tMOT\tAffiche les positions de MOT, si présent dans FILE\n"
"\t-P\t--phrases\tMOT\tAffiche les phrases contenant MOT dans FILE\n"
"\t-l\t--liste\tAffiche la liste des mots présents FILE, alphabetiquement\n"
"\t-d\t--prefixe\tPREFIX\tAffiche la liste des mots présents dans FILE dont PREFIXE est le prefixe.\n"
"\t-D\t--tofile\tOUTFILE\tSauvegarde la liste des mots dans OUTFILE.DICO\n"
"\n", version);
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
    if(argc == 1) {
        interactive_menu(tab, N, &alphab);
        exit(0);
    }

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
