#include "getdat.h"

// Вынуть метаданные
int get_meta(FILE *in)
{
    fscanf(in, "%s\n", meta.format);
    fscanf(in, "%d %d %d\n", &meta.num_of_vert, &meta.num_of_faces, &meta.num_of_edges);

    return 0;
}

// Вынуть точки в динамический массив и сформировать массив ребер из них
int get_data(FILE *in)
{
    int i, j;
    int v1, v2, v3;

    Vert *raw_vertix = (Vert*)malloc(sizeof(Vert) * meta.num_of_vert);
    Edge e_temp;

    same_vert = 0;
    for(i = 0; i < meta.num_of_vert; i++)
    {
        fscanf(in, "%f %f %f\n", &(raw_vertix[i].x), &(raw_vertix[i].y), &(raw_vertix[i].z));
        if(search_same_vert(raw_vertix[i], raw_vertix, i))
        {
            same_vert++;
        }
    }

    // Проход по файлу и запись в массив ребер
    v1 = v2 = v3 = 0;
    ed_num = 0;
    e_temp.sw = 1;
    for(i = 0, j = 0; i < meta.num_of_faces; i++)
    {
        fscanf(in, "3 %d  %d %d\n", &v1, &v2, &v3);

        vert_to_vert(&(e_temp.edge_vert[0]), &(raw_vertix[v1]));
        vert_to_vert(&(e_temp.edge_vert[1]), &(raw_vertix[v2]));
        if(search_same_edge(e_temp, EdgeMass, j) == -1)
        {
            add_edge(raw_vertix[v1], raw_vertix[v2], j);
            j++;
        }

        vert_to_vert(&(e_temp.edge_vert[0]), &(raw_vertix[v2]));
        vert_to_vert(&(e_temp.edge_vert[1]), &(raw_vertix[v3]));
        if(search_same_edge(e_temp, EdgeMass, j) == -1)
        {
            add_edge(raw_vertix[v2], raw_vertix[v3], j);
            j++;
        }

        vert_to_vert(&(e_temp.edge_vert[0]), &(raw_vertix[v1]));
        vert_to_vert(&(e_temp.edge_vert[1]), &(raw_vertix[v3]));
        if(search_same_edge(e_temp, EdgeMass, j) == -1)
        {
            add_edge(raw_vertix[v1], raw_vertix[v3], j);
            j++;
        }

        v1 = v2 = v3 = 0;
        if(j >= DEF_EDGE_MASS_SIZE - 3)
        {
            return 1;
        }
    }
    ed_num = j;
    EdgeMass[j].sw = 0;

    free(raw_vertix);
    return 0;
}

// Добавить ребро в массив
int add_edge(Vert v1, Vert v2, int ind)
{
    EdgeMass[ind].sw = 1;
    vert_to_vert(&(EdgeMass[ind].edge_vert[0]), &v1);
    vert_to_vert(&(EdgeMass[ind].edge_vert[1]), &v2);

    EdgeMass[ind].length = sqrt(((v2.x - v1.x) * (v2.x - v1.x)) + ((v2.y - v1.y) * (v2.y - v1.y)) + ((v2.z - v1.z) * (v2.z - v1.z)));

    return 0;
}

int read_file(char *filename)
{
    FILE *in;

    if(!(in = fopen(filename, "r")))
    {
        //printf("ERROR!: read_file()\n");
        //getchar();
        return -1;
    }

    get_meta(in);

    if(get_data(in))
    {
        return 1;
    }

    fclose(in);
    return 0;
}
