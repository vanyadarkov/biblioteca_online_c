/* CATRUC Ionel - 312CBa */

#include "TTrie.h"

//Functie care initializeaza un nod de Trie
TTrie init_nod()
{
    TTrie nod = NULL;
    nod = calloc(1, sizeof(Node));

    if(nod)
    {
        nod->info = NULL;
        nod->sf_cuv = 0;
        for(int i = 0; i < ALPHABET_SIZE; i++)
        {
            nod->child[i] = NULL;
        }
    }
    return nod;
}

//Insereaza in trie stringul primit
TTrie insert_trie(TTrie root, char * key)
{
    int length = strlen(key);
    int pos;

    TTrie p = root;
    for(int level = 0; level < length; level++)
    {
        //determin la ce pozitie trebuie sa adaug
        pos = get_pos(key[level]);
        //Daca nu exista nimic acolo - creeaza un nod nou
        if(!p->child[pos])
        {
            p->child[pos] = init_nod();
        }
        p = p->child[pos];
    }
    //Cand se ajunge la capat - seteaza sfarsit de cuvant
    p->sf_cuv = 1;
    return p;
}

//Cautare carte dupa prefix
//Primeste radacina care contine ultima litera a prefixului
//Nivel si found - cate elemente deja s-au gasit
void search_book_by_pref(TTrie root, int level, int * founds, FILE * fout)
{
    //Daca s-au gasit 3 - nu mai fa nimic
    if(*founds == 3) return;
    //Daca s-a gasit 
    //Afiseaza titlul si semnaleaza ca s-a gasit (found++)
    if(root->sf_cuv == 1)
    {
        fprintf(fout, "%s\n", GET_TITLE(root->info));
        (*founds)++;
    }
    //Parcurgem recursiv in adancime
    for(int i = 0; i < ALPHABET_SIZE; i++)
    {
        if(root->child[i])
        {
            search_book_by_pref(root->child[i], level + 1, founds, fout);
        }
    }
    return;
}

//Cautare dupa prefix
//Primeste radacina care contine ultima litera a prefixului
//str - stringul in care la fiecare nod gasit se va adauga caracterul
//de la adancimea la care se afla, adancimea
//found -cate elemente deja s-au gasit
void search_author_by_pref(TTrie root, char * str, int level, int * founds, FILE * fout)
{
    if(*founds == 3) return;
    if(root->sf_cuv == 1)
    {
        //Daca s-a gasit autor
        //Seteaza sfarsitul stringului
        str[level] = '\0';
        fprintf(fout, "%s\n", str);
        (*founds)++;
    }
    for(int i = 0; i < ALPHABET_SIZE; i++)
    {
        if(root->child[i])
        {
            //la pozitia str[level] adauga caracterul
            //specific numarului de ordine din alfabet
            str[level] = pos_to_char(i);
            search_author_by_pref(root->child[i], str,  level + 1, founds, fout);
        }
    }
    return;
}

//Cautare in trie dupa ref
//Returneaza NULL -> nimic nu s-a gasit
//Sau TTrie - celula la care s-a ajuns cand
//S-a terminat parcurgerea stringului
TTrie search_trie(TTrie root, char * ref)
{
    int index;
    int length = strlen(ref);
    TTrie p = root;
    for (int level = 0; level < length; level++)
    {
        index = get_pos(ref[level]);
        if(p->child[index] == NULL)
        {
            return NULL;
        }
        p = p->child[index];
    }
    if(p != NULL)
    {
        return p;
    }
    return NULL;
}

//Verifica daca celula root primit nu mai are copii
int is_empty(TTrie root)
{
    for(int i = 0; i < ALPHABET_SIZE; i++)
    {
        if(root->child[i] != NULL)   return 0;
    }
    return 1;
}

//Functie recursiva de sterge a unei ref din trie
TTrie delete_from_trie(TTrie root, char * ref, int level)
{
    if(!root) 
        return NULL;
    if(level == strlen(ref))
    {
        if(root->sf_cuv == 1) root->sf_cuv = 0;
        if(root->info != NULL) free_book(root->info);
        if(is_empty(root))
        {
            free(root);
            root = NULL;
        }
        return root;
    }
    int index = get_pos(ref[level]);
    root->child[index] = delete_from_trie(root->child[index], ref, level + 1);

    if(is_empty(root) && root->sf_cuv == 0)
    {
        free(root);
        root = NULL;
    }
    return root;
}

//Funtie de printare a trie-ului de titluri a cartilor
void print_trie(TTrie root, int level, FILE * fout)
{
    //Conditie de intoarcere din recursivitate
    if(!root) return;
    
    if(root->sf_cuv == 1)
    {
        //Daca s-a gasit sfarsitul de cuvant 
        //Extrage titlul din aceasta celula
        //Si afiseaza
        fprintf(fout, "%s\n", GET_TITLE(root->info));
    }
    //Parcurge vectorul de copii
    for(int i = 0; i < ALPHABET_SIZE; i++)
    {
        //Daca exista copil -> parcurgem 
        if(root->child[i])
        {
            print_trie(root->child[i], level + 1, fout);
        }
    }
}

//Eliberare T1 sau trie de titluri
void free_trie_1(TTrie root)
{
    if(root->sf_cuv)
    {
        free_book(root->info);
    }
    for(int i = 0; i < ALPHABET_SIZE; i++)
    {
        if(root->child[i]) 
            free_trie_1(root->child[i]);
    }
    free(root);
    root = NULL;
}

//Elibereaza T2, iar pentru titlurile autorului Foloseste free_trie_1
void free_trie_2(TTrie root)
{
    if(root->sf_cuv)
    {
        free_trie_1(root->info);
    }
    for(int i = 0; i < ALPHABET_SIZE; i++)
    {
        if(root->child[i]) 
            free_trie_2(root->child[i]);
    }
    free(root);
    root = NULL;
}

//Functie de determinare a pozitie in alfabet a caracterului c
int get_pos(char  c) 
{
    if(c >= 'A' && c <= 'Z')
    {
        return 'z' - 'a' + 1 + c - 'A';
    }
    if(c >= '0' && c <= '9')
    {
        return 2 * ('z' - 'a') + 2 + c - '0';
    }
    if(c >= 'a' && c <= 'z')
    {
        return c - 'a';
    }
    if(c == ' ')
    {
        return ALPHABET_SIZE - 1;
    }
    if(c == '!')
    {
        return ALPHABET_SIZE - 2;
    }
    if(c == '?')
    {
        return ALPHABET_SIZE - 3;
    }
    if(c == '\'')
    {
        return ALPHABET_SIZE - 4;
    }
    if(c == '-')
    {
        return ALPHABET_SIZE - 5;
    }
    if(c == '.')
    {
        return ALPHABET_SIZE - 6;
    }
    return -1;
}

//Functie de determinare a caracterului care se afla la pozitia
//pos in alfabet
char pos_to_char(int pos) 
{
    if(pos >= 26 && pos <= 51)
    {
        return (char)(pos - 'z' + 'a' - 1 + 'A');
    }
    if(pos >= 52 && pos <= 61)
    {
        return (char)(pos - 2 +'0' - 2*('z' - 'a'));
    }
    if(pos >= 0 && pos <= 25)
    {
        return (char)(pos + 'a');
    }
    if(pos == ALPHABET_SIZE - 1)
    {
        return ' ';
    }
    if(pos == ALPHABET_SIZE - 2)
    {
        return '!';
    }
    if(pos == ALPHABET_SIZE - 3)
    {
        return '?';
    }
    if(pos == ALPHABET_SIZE - 4)
    {
        return '\'';
    }
    if(pos == ALPHABET_SIZE - 5)
    {
        return '-';
    }
    if(pos == ALPHABET_SIZE - 6)
    {
        return '.';
    }
    return -1;
}