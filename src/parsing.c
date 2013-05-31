#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "parsing.h"
#include "hachage.h"

#define SENTENCE_BUFFER_LEN 65535


int parse_file(Cellule* tab, long size_of_tab, char* fname, Liste* alphabetical_word_list) {
    FILE* f = fopen(fname, "r");
    unsigned long global_index = 0, sentence_offset = 0;
    unsigned char line[SENTENCE_BUFFER_LEN];
    unsigned short line_index;
    unsigned char c;
    line_index = 0;
    sentence_offset = global_index;
    while(!feof(f) && (c = tolower(fgetc(f)))) {
        global_index++;
        if(c == '.' || c == '!' || c == '?'){
            parse_sentence(tab, size_of_tab, line, line_index + 1, sentence_offset, alphabetical_word_list);
            /* reset current line */
            for(line_index = 0; line_index < SENTENCE_BUFFER_LEN; ++line_index)
                line[line_index] = 0;
            line_index = 0;
            sentence_offset = global_index + 1;
        }
        else
            line[line_index++] = c;
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
    /* Here we have a problem, since we have to count also the word index. So i will rewrite this func */
    unsigned char* mot = calloc(sentence_len, sizeof(unsigned char));
    unsigned short i = 0;
    unsigned short mot_index = 0;
    while(sentence[i] != '\0') {
        if(sentence[i] == ' ' || sentence[i] == ',' || sentence[i] == ';' || sentence[i] == '\n'){
            /* the we have to add the current word to the list, and cleanup the current word*/
            if(strcmp((const char*) mot, "") != 0 && strcmp((const char*) mot, " ") !=  0 && strcmp((const char*) mot, ".") != 0) {
                add_word(tab, size_of_tab, mot, i + 1, sentence_pos, alphabetical_word_list);
                mot_index = 0;
                for(; mot_index<sentence_len; mot_index++)
                    mot[mot_index] = 0;
                mot_index = 0;
            }
            else
                i++;
        }
        else {
            mot[mot_index++] = sentence[i++];
        }
    }
    free(mot);
    return 1;
}

int add_word(Cellule* tab, long size_of_tab, unsigned char* word, unsigned short word_len, unsigned long sentence_pos, Liste* alphabetical_word_list) {
    int hash = hache((char*) word);
    Liste l = &tab[hash % size_of_tab]; /* we get the address of the row we have to write to */
    Liste orig = l;

    /* we have to add it at the end of the cell list. */
    /*
    do {
        if(l->valeur != NULL  && strcmp((const char*)l->valeur->mot, (const char*) word) == 0) {
            celmot_add_position(l->valeur, sentence_pos);
            return 1;
        }
        if(l->suivant == NULL)
            break;
        l = l->suivant;
    } while(l->suivant != NULL);
    Liste to_add;
    if(l->valeur == NULL)
        to_add = l;
    else
        to_add = liste_new(); */
    char* word_to_add = malloc(sizeof(char) * (word_len));
    strcpy(word_to_add, word);
    Celmot* elem = celmot_new(word_to_add);
    celmot_add_position(elem, sentence_pos);
    /* to_add->valeur = elem; */
    /* if(l != to_add) */
    liste_add_alphabetical(&orig, elem);
    /*     liste_add(&l, to_add); */
    liste_add_alphabetical(alphabetical_word_list, elem);
    return 1;
}
