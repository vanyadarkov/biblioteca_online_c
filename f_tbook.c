/* CATRUC Ionel - 312CBa */

#include "Tbook.h"

TBook init_book(char * title, char * author, int rating, int nr_of_pages)
{
    TBook book = calloc(1, sizeof(Book));
    if(!book) return NULL;
    book->author = calloc(MAX_AUTHOR, sizeof(char));
    if(!book->author)
    {
        free(book);
        return NULL;
    }
    book->title = calloc(MAX_TITLE, sizeof(char));
    if(!book->author)
    {
        free(book->author);
        free(book);
        return NULL;
    }
    strcpy(book->author, author);
    strcpy(book->title, title);
    book->rating = rating;
    book->nr_of_pages = nr_of_pages;
    return book;
}

void free_book(void * x)
{
    TBook book = x;
    free(book->author);
    free(book->title);
    free(book);
    x = NULL;
}

void print_book(void *x, FILE * fout)
{
    TBook b = x;
    fprintf(fout, "Informatii recomandare: %s, %s, %d, %d\n", b->title, b->author, b->rating, b->nr_of_pages);
}