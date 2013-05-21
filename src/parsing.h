#ifndef __PARSING_H__
#define __PARSING_H__

#include "structs/cellule.h"

int parse_file(Cellule* tab, long size_of_tab, char* fname, Liste* alphabetical_word_list);

int parse_sentence(Cellule* tab, long size_of_tab, unsigned char* sentence, unsigned short sentence_len, unsigned long sentence pos, Liste* alphabetical_word_list);

int add_word(Cellule* tab, long size_of_tab, unsigned char* word, unsigned short word_len, Liste* alphabetical_word_list);

#endif
