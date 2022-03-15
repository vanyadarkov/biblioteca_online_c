/* CATRUC Ionel - 312CBa */

#include "in_utlis.h"
#include "TTrie.h"
#include "Tbook.h"


int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Argumente insuficiente\n");
        return -1;
    }

    FILE * input_file = fopen(argv[1], "r");
    FILE * output_file = fopen(argv[2], "w");
    if(!input_file || !output_file)
    {
        fprintf(stderr, "Eroare deschidere unul din fisiere\n");
        return -1;
    }
    read_input(input_file, output_file);
    fclose(input_file);
    fclose(output_file);
    return 0;
}