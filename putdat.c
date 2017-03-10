#include "putdat.h"

int write_file(char *filename, int len)
{
    int i;

    FILE *out;

    if(!(out = fopen(filename, "w")))
    {
        printf("ERROR!: write_file()\n");
        return -1;
    }

    for(i = 0; i < len; i++)
    {
        fprintf(out, "%c", M[i]);
    }

    printf("Writing file\n");

    return 0;
}
