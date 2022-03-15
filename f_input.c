/* CATRUC Ionel - 312CBa */

#include "in_utlis.h"

void read_input(FILE * fin, FILE * fout)
{
    char * line = malloc(MAX_LINE * sizeof(char));
    char * command;
    //Initializez arborii
    TTrie T1 = init_nod();
    if(!T1)
    {
        fprintf(stderr, "Eroare alocare T1\n");
        return;
    }
    TTrie T2 = init_nod();
    if(!T2)
    {
        free(T1);
        fprintf(stderr, "Eroare alocare T2\n");
        return;
    }
    if(!line) return;
    while(fgets(line, MAX_LINE, fin) != NULL)
    {
        //Anulare \n la sfarsitul unei noi linii citite
        if(line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
        //Skip daca e o linie vida
        if(strcmp(line,"") == 0) continue;
        
        command = strtok(line, " ");
        
        if(strcmp(command, "add_book") == 0)
        {
            char * title = strtok(NULL,":");
            //Caut cartea in T1
            TTrie search_result = search_trie(T1, title);
            if(search_result != NULL)
            {
                if(search_result->sf_cuv == 1)
                {
                    //Daca cartea a fost gasita - treci mai departe
                    if(strcmp(GET_TITLE(search_result->info), title) == 0)
                    continue;
                }
            }
            //Extrag informatia
            char * author = strtok(NULL,":");
            int rating = atoi(strtok(NULL,":"));
            int nr_of_pages = atoi(strtok(NULL,":"));
            //Aloc structurile pentru carti
            TBook book = init_book(title, author, rating, nr_of_pages);
            TBook book1 = init_book(title, author, rating, nr_of_pages);
            TTrie last;
            //Inserez in T1
            last = insert_trie(T1, title);
            //Celulei cu ultima litera completez info cu cartea            
            last->info = book;
            //Inserez in T2
            last = insert_trie(T2, author);
            //Daca autorul apare pentru prima data
            if(last->info == NULL)
            {
                //Creeaza un arbore nou pentru cartile sale
                TTrie aux = init_nod();
                //Insereaza titlul
                TTrie p = insert_trie(aux, title);
                //Ultimei litere a titlului adaugat ii atribuim structura carti
                p->info = book1;
                //Ultimei litere a numelui autorului ii dam arborele sau de titluri
                last->info = aux;
            }
            //Daca autorul deja era
            else
            {
                //Insereaza cartea ii arborele sau de carti
                TTrie aux = insert_trie(last->info, title);
                aux->info = book1;
            }
        }
        if(strcmp(command, "search_book") == 0)
        {
            char * title = strtok(NULL, "\0");
            TTrie result;
            //Daca cautam dupa prefix
            if(title[strlen(title) - 1] == '~')
            {
                title[strlen(title) - 1] = '\0';
                //Cautam cartea
                result = search_trie(T1, title);
                if(!result)
                    fprintf(fout, "Nicio carte gasita.\n");
                else
                {
                    int founds = 0;
                    //Incepem sa cautam din radacina gasita care contine pref
                    search_book_by_pref(result, 0, &founds, fout);
                    //Daca found e != 0 - nu fa nimic deoarece afisarea se face in
                    //Functie
                    //De altfel afiseaza ca cartea nu a fost gasita
                    founds ? : fprintf(fout, "Nicio carte gasita.\n");
                }
            }
            else
            {
                result = search_trie(T1, title);
                if(!result)
                    fprintf(fout ,"Cartea %s nu exista in recomandarile tale.\n", title);
                else
                {   //Daca cartea a fost gasita si e sfarsit de cuvant celula intoarsa
                    //Atunci afiseaza cartea
                    if(result->sf_cuv == 1) print_book(result->info, fout);
                    else fprintf(fout ,"Cartea %s nu exista in recomandarile tale.\n", title);
                }
            }
        }
        if(strcmp(command, "list_author") == 0)
        {
            char * author = strtok(NULL, "\0");
            TTrie result;
            if(author[strlen(author) - 1] == '~')
            {   
                author[strlen(author) - 1] = '\0';
                result = search_trie(T2, author);
                if(!result)
                    fprintf(fout, "Niciun autor gasit.\n");
                else
                {
                    int founds = 0;
                    //Aloc un string auxiliar
                    char * aux = calloc(MAX_AUTHOR, sizeof(char));
                    if(!aux)
                    {
                        fprintf(stderr, "Eroare alocare aux\n");
                        return;
                    }
                    //Copii in aux prefixul autorului cautat
                    strcpy(aux, author);
                    //Efectuez cautare
                    search_author_by_pref(result, aux, strlen(aux), &founds, fout);
                    founds ? : fprintf(fout, "Niciun autor gasit.\n");
                    free(aux);
                }    
            }
            else
            {
                result = search_trie(T2, author);
                if(!result) 
                    fprintf(fout, "Autorul %s nu face parte din recomandarile tale.\n", author);
                else
                {
                    if(result->sf_cuv == 1) print_trie(result->info, 0, fout);
                    else fprintf(fout, "Autorul %s nu face parte din recomandarile tale.\n", author);
                }
            }
        }
        if(strcmp(command, "search_by_author") == 0)
        {
            char * author = strtok(NULL, ":");
            char * title = strtok(NULL, "\0");
            TTrie result;
            if(author[strlen(author) - 1] == '~')
            {   
                author[strlen(author) - 1] = '\0';
                result = search_trie(T2, author);
                if(!result)
                    fprintf(fout, "Niciun autor gasit.\n");
                else
                {
                    //Similar ca la list author dupa prefix
                    int founds = 0;
                    char * aux = calloc(MAX_AUTHOR, sizeof(char));
                    if(!aux) return;
                    strcpy(aux, author);
                    search_author_by_pref(result, aux, strlen(aux), &founds, fout);
                    founds ? : fprintf(fout, "Niciun autor gasit.\n");
                    free(aux);
                }    
            }
            else if (title[strlen(title) - 1] == '~')
            {
                title[strlen(title) - 1] = '\0';
                //Cautam autorul in T2
                result = search_trie(T2, author);
                if(!result)
                    fprintf(fout, "Autorul %s nu face parte din recomandarile tale.\n", author);
                else
                {
                    if(result->sf_cuv == 1)
                    {
                        //Daca a fost gasit autorul
                        //Cauta prefixul in Trie-ul cartilor sale
                        result = search_trie(result->info, title);
                        if(!result)
                            fprintf(fout, "Nicio carte gasita.\n");
                        else
                        {
                            //Similar ca la search_book dupa prefix
                            int founds = 0;
                            search_book_by_pref(result,0, &founds, fout);
                            founds ? : fprintf(fout, "Nicio carte gasita.\n"); 
                        }
                    }
                    else fprintf(fout, "Autorul %s nu face parte din recomandarile tale.\n", author);
                }    
            }
            else
            {
                //Daca cautam fara nici un prefix de auto-complete
                //Cautam autorul
                result = search_trie(T2, author);
                if(!result) 
                    fprintf(fout, "Autorul %s nu face parte din recomandarile tale.\n", author);
                else
                {
                    if(result->sf_cuv == 1)
                    {
                        //Daca l-am gasit cautam cartea
                        result = search_trie(result->info, title);
                        if(!result)
                            fprintf(fout ,"Cartea %s nu exista in recomandarile tale.\n", title);
                        else
                        {
                            //Daca cartea exista afiseaz-o
                            if(result->sf_cuv == 1) print_book(result->info, fout);
                            else fprintf(fout ,"Cartea %s nu exista in recomandarile tale.\n", title);
                        }
                    }
                    else fprintf(fout, "Autorul %s nu face parte din recomandarile tale.\n", author);
                }
            }
        }
        if(strcmp(command, "delete_book") == 0)
        {
            char * title = strtok(NULL, "\0");
            TTrie book = search_trie(T1, title);
            //Cautam daca cartea exista
            if(!book)
            {
                fprintf(fout, "Cartea %s nu exista in recomandarile tale.\n", title);
                continue;
            }
            if(book->sf_cuv == 0)
            {
                fprintf(fout, "Cartea %s nu exista in recomandarile tale.\n", title);
                continue;
            }
            //Daca cartea a fost gasita
            else if(book->sf_cuv == 1)
            {
                char * author = GET_AUTHOR(book->info);
                //Cautam autorul cartii in T2
                TTrie author_books = search_trie(T2, author);
                if(author_books->sf_cuv == 1)
                {
                    //Daca autorul cartii a fost gasit
                    //Stergem din Trie-ul cartilor salea cartea
                    author_books->info = delete_from_trie(author_books->info, title, 0);
                    if(author_books->info == NULL)
                    {
                        //Daca nu mai exista nici o carte a autorului
                        //Elibereaza Trie-ul cartilor sale
                        free(author_books->info);
                        //Sterge autorul din T2
                        delete_from_trie(T2, author, 0);
                    }
                    //Sterge titlul din T1
                    delete_from_trie(T1, title, 0);
                }
            }
        }
    }
    free(line);
    free_trie_2(T2);
    free_trie_1(T1);
}