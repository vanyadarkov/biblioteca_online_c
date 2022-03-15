/* CATRUC Ionel - 312CBa */

#ifndef _TYPE_BOOK_
#define _TYPE_BOOK_

#include "in_utlis.h"

//Lungimea maxima a titlului
#define MAX_TITLE 51
//Lungimea maxima a numelui autorului
#define MAX_AUTHOR 41


typedef struct _book_
{
    char * title;
    char * author;
    int rating;
    int nr_of_pages;
}Book, *TBook;

//Extrage titlul din void* primit(care sigur pointeaza catre o structura
//de tip TBook)
#define GET_TITLE(a) ((TBook)a)->title
//Extrage autorul din void* primit(care sigur pointeaza catre o structura
//de tip TBook)
#define GET_AUTHOR(a)   ((TBook)a)->author

TBook init_book(char * title, char * author, int rating, int nr_of_pages);
void print_book(void *x, FILE * fout);
void free_book(void * x);

#endif