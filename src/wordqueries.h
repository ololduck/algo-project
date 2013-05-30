#ifndef __WORDQUERIES_H__
#define __WORDQUERIES_H__

#include "structs/cellule.h"

int belongs(char* word, Cellule* tab, int tab_len);
void print_positions(char* word, Cellule* tab, int tab_len);
void print_sentences_containing_word(char* word, char* fname, Cellule* tab, int tab_len);
void print_alphabetical(Liste l);
int print_all_from_prefix(char* prefix, Liste l);
void save_positions_to_file(char* filename, Liste l);

#endif
