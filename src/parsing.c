#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parsing.h"
#include "hachage.h"

#define SENTENCE_BUFFER_LEN 65535


int parse_file(Cellule* tab, long size_of_tab, char* fname, Liste* alphabetical_word_list) {
    FILE* f = fopen(fname, 'r');
    unsigned long global_index = 0, sentence_offset = 0;
    unsigned char line[SENTENCE_BUFFER_LEN];
    unsigned short line_index;
    unsigned char c;
    while(!feof(f)){
        line_index = 0;
        sentence_offset = global_index;
        while(!feof(f) && (c = tolower(fgetc(f)))) {
            global_index++;
            if(c == '.' || c == '!' || c == '?'){
                parse_sentence(tab, size_of_tab, line, line_index + 1, sentence_offset, alphabetical_word_list);
                /* reset current line */
            }
            line[line_index++] = c;
        }
    }
    fclose(f);
    return 1;
}

int parse_sentence(Cellule* tab,
    long size_of_tab,
    unsigned char* sentence,
    unsigned short sentence_len,
    unsigned long sentence_pos,
    Liste* alphabetical_word_list) {
    unsigned char* mot = calloc(sentence_len, sizeof(unsigned char));
    unsigned short i = 0;
    while(sentence[i] != '\0') {
        if(sentence[i] == ' ' || sentence[i] == ',' || sentence[i] == ';'){
            /* the we have to add the current word to the list, and cleanup the current word*/
            add_word(tab, size_of_tab, mot, i + 1, sentence_pos, alphabetical_word_list);
            int tmp = 0;
            for(; tmp<sentence_len; tmp++)
                mot[tmp] = 0;
        }
        mot[i] = sentence[i++];
    }
    return 1;
}

int add_word(Cellule* tab, long size_of_tab, unsigned char* word, unsigned short word_len, unsigned long sentence_pos, Liste* alphabetical_word_list) {
    char* word_to_add = malloc(sizeof(char) * (word_len));
    strcpy(word_to_add, word);
    int hash = hache(word_to_add);
    Liste l = &tab[hash % size_of_tab]; /* we get the address of the row we have to write to */
    Celmot* elem = celmot_new(word_to_add);
    Liste to_add = liste_new();
    to_add->valeur = elem;
    celmot_add_position(elem, sentence_pos);
    liste_add_alphabetical(alphabetical_word_list, elem);
    return 1;
}
