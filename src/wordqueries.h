#ifndef __WORDQUERIES_H__
#define __WORDQUERIES_H__

#include "structs/cellule.h"

/**
 * checks for presence of a word in a file
 * @param  word    THe word to search for
 * @param  tab     the array containing the data
 * @param  tab_len the array length
 * @return         0 if not found, else 1
 */
int belongs(char* word, Cellule* tab, int tab_len);

/**
 * prints on screen the positions of a given word
 */
void print_positions(char* word, Cellule* tab, int tab_len);

/**
 * prints on screen the sentences containing the word
 * @param word    [description]
 * @param fname   The file used to generate the hashmap, so we can read all the sentences
 * @param tab     [description]
 * @param tab_len [description]
 */
void print_sentences_containing_word(char* word, char* fname, Cellule* tab, int tab_len);

/**
 * prints on screen the entire liste of words, sorted alphabetically.
 * @param l the ordered list
 */
void print_alphabetical(Liste l);

/**
 * print all words matching PREFIX
 * @param  prefix the prefix to use for matching
 * @param  l      the list, sorted alphabetically
 */
int print_all_from_prefix(char* prefix, Liste l);

/**
 * Saves the entire list of words in a given file, alphabetically
 * @param filename the filename to use. ".DICO" will be appended if not found.
 * @param l        the liste, sorted alphabetically
 */
void save_positions_to_file(char* filename, Liste l);

#endif
