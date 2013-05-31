#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wordqueries.h"

static Liste get(char* word, Liste l) {
    while(l != NULL) {
        Celmot* tmpword = l->valeur;
        if(tmpword != NULL) {
            if(strcmp(word, tmpword->mot) == 0)
                return l;
        }
        l = l->suivant;
    }
    return NULL;
}

static void print_word_and_pos_to_fd(FILE* fd, Celmot* m) {
    if(m->mot != NULL) {
        fprintf(fd,"%s", m->mot);
        Listepos pos = m->positions;
        while(pos != NULL) {
            fprintf(fd," %d", pos->position);
            pos = pos->suivant;
        }
        fprintf(fd,"\n");
    }
}

static void print_liste_to_fd(FILE* fd, Liste l) {
    while(l != NULL) {
        if(l->valeur != NULL) {
            Celmot* m = l->valeur;
            print_word_and_pos_to_fd(fd, m);
        }
        l = l->suivant;
    }
}

static void print_sentence(FILE* f, int pos) {
    fseek(f, pos, SEEK_SET);
    char c;
    while((c = fgetc(f)) != EOF && c != '.' && c != '!' && c!='?') {
        printf("%c", c);
    }
}

int belongs(char* word, Cellule* tab, int tab_len) {
    int hash = hache(word);
    Liste l = &tab[hash % tab_len];
    if(get(word, l) != NULL)
        return 1;
    return 0;
}

void print_positions(char* word, Cellule* tab, int tab_len) {
    int hash = hache(word);
    Liste l = &tab[hash % tab_len];
    l = get(word, l);
    if(l != NULL) {
        Listepos pos = l->valeur->positions;
        while(pos != NULL){
            printf("%d ", pos->position);
            pos = pos->suivant;
        }
        printf("\n");
    }
    else
        fprintf(stderr, "Word not found: %s\n", word);
}

void print_sentences_containing_word(char* word, char* fname, Cellule* tab, int tab_len) {
    int hash = hache(word);
    Liste l = &tab[hash % tab_len];
    FILE* f = fopen(fname, "r");
    if(f == NULL) {
        fprintf(stderr, "Error while trying to read file %s\n", fname);
        exit(1);
    }
    l = get(word, l);
    if( l != NULL) {
        Listepos pos = l->valeur->positions;
        while(pos != NULL) {
            print_sentence(f, pos->position);
            pos = pos->suivant;
        }
        printf("\n");
    }
    else
        fprintf(stderr, "Word not found: %s\n", word);
}

void print_alphabetical(Liste l) {
    print_liste_to_fd(stdout, l);
}

void save_positions_to_file(char* filename, Liste l) {
    if(strstr(filename, ".dico") == NULL && strstr(filename, ".DICO") == NULL)
        strcat(filename, ".DICO");
    FILE* f = fopen(filename, "w+");
    if(f==NULL) {
        fprintf(stderr, "Error trying to open file %s", filename);
        exit(1);
    }
    print_liste_to_fd(f, l);
}

int print_all_from_prefix(char* prefix, Liste l) {
    int retcode = 0;
    while(l != NULL) {
        if(l->valeur != NULL) {
            Celmot* m = l->valeur;
            if(m->mot != NULL) {
                char* res = strstr(m->mot, prefix);
                if(res == m->mot) {
                    /* then the substring is located at the beginning of the string */
                    print_word_and_pos_to_fd(stdout, m);
                    retcode = 1;
                }
            }
        }
        l = l->suivant;
    }
    return retcode;
}
