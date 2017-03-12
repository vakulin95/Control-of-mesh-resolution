#include "putdat.h"

int open_info(char *filename, char *filename_m)
{
    if(!(out_m = fopen(filename_m, "w")))
    {
        printf("ERROR!: write_meta()\n");
        return -1;
    }

    return 0;
}

int inp_info(char *filename)
{
    fprintf(out_m, "Name:\t%s\n\n", filename);
    fprintf(out_m, "Format:\t%s\nVert:\t%d\nFaces:\t%d\nEdges:\t%d\n\n",
            meta.format, meta.num_of_vert, meta.num_of_faces, meta.num_of_edges);

    if(same_vert)
    {
        fprintf(out_m, "Number of same vertices:\t%d\n\n", same_vert);
    }
    else
    {
        fprintf(out_m, "No same vertices!\n\n");
    }

    fprintf(out_m, "\n----------------------------------------------------------\n");
    return 0;
}

int write_file(char *filename)
{
    int i;

    FILE *out;

    if(!(out = fopen(filename, "w")))
    {
        printf("ERROR!: write_file()\n");
        return -1;
    }

    //printf("Writing file\n");
    fclose(out);
    return 0;
}
