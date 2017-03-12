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

    if(same_vert)
    {
        printf("\nNumber of same vertices: %d\n", same_vert);
    }

    // Проход по файлу и запись в массив ребер
    v1 = v2 = v3 = 0;
    ed_num = 0;
    for(i = 0, j = 0; i < meta.num_of_faces; i++)
    {
        fscanf(in, "3 %d  %d %d\n", &v1, &v2, &v3);

        EdgeMass[j].sw = 1;
        vert_to_vert(&(EdgeMass[j].edge_vert[0]), raw_vertix[v1]);
        vert_to_vert(&(EdgeMass[j].edge_vert[1]), raw_vertix[v2]);
        j++;

        EdgeMass[j].sw = 1;
        vert_to_vert(&(EdgeMass[j].edge_vert[0]), raw_vertix[v2]);
        vert_to_vert(&(EdgeMass[j].edge_vert[1]), raw_vertix[v3]);
        j++;

        EdgeMass[j].sw = 1;
        vert_to_vert(&(EdgeMass[j].edge_vert[0]), raw_vertix[v1]);
        vert_to_vert(&(EdgeMass[j].edge_vert[1]), raw_vertix[v3]);
        j++;

        v1 = v2 = v3 = 0;
    }
    ed_num = j;
    EdgeMass[j].sw = -1;

    // printf("\nEdges num: %d\n", ed_num);
    // for(i = ed_num - 10; i < ed_num; i++)
    // {
    //     print_edge(EdgeMass[i]);
    // }

    free(raw_vertix);
    return 0;
}

//-------------------------------------------------------------------------//

// Поиск одинаковых точек в массиве
int search_same_vert(Vert vertix, Vert *Array, int size)
{
    int i;

    for(i = 0; i < size; ++i)
    {
        if(vertix.x == Array[i].x && vertix.y == Array[i].y && vertix.z == Array[i].z)
            return 1;
    }

    return 0;
}

// Поиск одинаковых ребер в массиве
// Если найдено, возврат индекса, иначе -1
int search_same_edge(Edge edge, Edge *Array, int size)
{
    int i;
    int Y = -1;

    for(i = 0; i < size; ++i)
    {
        if(comp_edges(edge, Array[i]))
        {
            Y = i;
            goto ret;
        }
    }
ret:
    return Y;
}

// Сравнить две точки
int comp_vert(Vert v1, Vert v2)
{
    int Y = -1;

    if(v1.x == v2.x && v1.y == v2.y && v1.z == v2.z)
    {
        Y = 1;
        goto ret;
    }
    else if(v1.x != v2.x || v1.y != v2.y || v1.z != v2.z)
    {
        Y = 0;
        goto ret;
    }

    printf("FATAL ERROR!: comp_vert()\n");
    getchar();
ret:
    return Y;
}

// Присвоить одну точку другой
int vert_to_vert(Vert *v1, Vert v2)
{
    // print_vert(*v1);
    // print_vert(v2);
    // printf("\n");

    v1->x = v2.x;
    v1->y = v2.y;
    v1->z = v2.z;

    return 0;
}

// Вывод точки в консоль
int print_vert(Vert v)
{
    printf("%f %f %f\n", v.x, v.y, v.z);

    return 0;
}

// Вывод ребра в консоль
int print_edge(Edge e)
{
    print_vert(e.edge_vert[0]);
    print_vert(e.edge_vert[1]);
    printf("\n");

    return 0;
}

// Сравнить два ребра
int comp_edges(Edge e1, Edge e2)
{
    int Y = -1;

    if(e1.sw && e2.sw)
    {
        if(comp_vert(e1.edge_vert[0], e2.edge_vert[0]) && comp_vert(e1.edge_vert[1], e2.edge_vert[1]))
        {
            Y = 1;
            goto ret;
        }
        else if(comp_vert(e1.edge_vert[1], e2.edge_vert[0]) && comp_vert(e1.edge_vert[0], e2.edge_vert[1]))
        {
            Y = 1;
            goto ret;
        }
        else if(comp_vert(e1.edge_vert[0], e1.edge_vert[1]) || comp_vert(e2.edge_vert[0], e2.edge_vert[1]))
        {
            printf("Some edge has 2 same vertices!\nProgram is interrupted.\n");
            getchar();
            Y = -2;
            goto ret;
        }
        else
        {
            Y = 0;
            goto ret;
        }
    }
    else
    {
        Y = 0;
        goto ret;
    }
ret:
    return Y;
}

//-------------------------------------------------------------------------//

int read_file(char *filename)
{
    char buff;
    int i;

    FILE *in;

    if(!(in = fopen(filename, "r")))
    {
        printf("ERROR!: read_file()\n");
        getchar();
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
