#include "getdat.h"

int get_meta(FILE *in)
{
    fscanf(in, "%s\n", meta.format);
    fscanf(in, "%d %d %d\n", &meta.num_of_vert, &meta.num_of_faces, &meta.num_of_edges);

    return 0;
}

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

    get_meta(in);

    printf("Name:\t%s\n", filename);
    printf("Format:\t%s\nvert:\t%d\nfaces:\t%d\nedges:\t%d\n",
            meta.format, meta.num_of_vert, meta.num_of_faces, meta.num_of_edges);

    //printf("Reading file\n");

    return 0;
}
