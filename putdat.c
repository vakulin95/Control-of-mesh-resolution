#include "putdat.h"

int write_file(char *filename)
{
    int i;

    FILE *out;

    if(!(out = fopen(filename, "w")))
    {
        printf("ERROR!: write_file()\n");
        return -1;
    }

    printf("Writing file\n");

    return 0;
}
