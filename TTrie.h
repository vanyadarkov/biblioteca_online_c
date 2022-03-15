/* CATRUC Ionel - 312CBa */

#ifndef _TYPE_TRIE_
#define _TYPE_TRIE_

#include "in_utlis.h"

//Dimensiunea alfabetului
#define ALPHABET_SIZE 68

typedef struct trie_node
{
    void * info;
    struct trie_node *child[ALPHABET_SIZE];
    int sf_cuv;
} Node, *TTrie;


TTrie init_nod();

TTrie insert_trie(TTrie root, char * key);

void print_trie(TTrie root, int level, FILE * fout);

TTrie search_trie(TTrie root, char * ref);

void search_book_by_pref(TTrie root, int level, int * founds, FILE * fout);

void search_author_by_pref(TTrie root, char * str, int level, int * founds, FILE * fout);

int is_empty(TTrie root);

TTrie delete_from_trie(TTrie root, char * ref, int level);

void free_trie_1(TTrie root);
void free_trie_2(TTrie root);

int get_pos(char c);
char pos_to_char(int pos);
#endif