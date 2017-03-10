#include "getdat.h"

int read_file(char *filename)
{
    char buff;
    int i;

    FILE *in;

    if(!(in = fopen(filename, "r")))
    {
        printf("ERROR!: read_file()\n");
        return -1;
    }

    i = 0;
    buff = fgetc(in);
    while(buff != EOF && i < N)
    {
        M[i] = buff;
        buff = fgetc(in);
        i++;
    }

    printf("Reading file\n");

    return i;
}
