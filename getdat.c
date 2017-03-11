#include "getdat.h"

// Вынуть метаданные
int get_meta(FILE *in)
{
    fscanf(in, "%s\n", meta.format);
    fscanf(in, "%d %d %d\n", &meta.num_of_vert, &meta.num_of_faces, &meta.num_of_edges);

    return 0;
}

// Вынуть точки в динамический массив
int get_data(FILE *in)
{
    int i;

    Vert *raw_vertix = (Vert*)malloc(sizeof(Vert) * meta.num_of_vert);
    Vert b;

    same_vert = 0;
    for(i = 0; i < meta.num_of_vert; i++)
    {
        fscanf(in, "%f %f %f\n", &(raw_vertix[i].x), &(raw_vertix[i].y), &(raw_vertix[i].z));
        if(search_same_vert(raw_vertix[i], raw_vertix, i))
        {
            same_vert++;

            // raw_vertix[i].x = -1;
            // raw_vertix[i].y = -1;
            // raw_vertix[i].z = -1;

            //printf("%f %f %f\n", (raw_vertix[i].x), (raw_vertix[i].y), (raw_vertix[i].z));
        }
    }

    // for(i = 0; i < meta.num_of_vert; i++)
    // {
    //     printf("%f %f %f\n", (raw_vertix[i].x), (raw_vertix[i].y), (raw_vertix[i].z));
    // }

    if(same_vert)
    {
        printf("\nNumber of same vertices: %d\n", same_vert);
    }

    free(raw_vertix);
    return 0;
}

// Поиск одинаковых точек в массиве
int search_same_vert(Vert vertix, Vert *Array, int size)
{
    int i;

    for(i = 0; i < size; i++)
    {
        if(vertix.x == Array[i].x && vertix.y == Array[i].y && vertix.z == Array[i].z)
            return 1;
    }

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

    get_data(in);
    //printf("Reading file\n");

    return 0;
}
