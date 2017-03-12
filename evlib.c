#include "evlib.h"

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

//-----------------------------------------------------------------------------//

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

// Вывод ребра в консоль
int print_edge(Edge e)
{
    printf("switched:\t%d\n", e.sw);
    printf("length  :\t%f\n", e.length);

    print_vert(e.edge_vert[0]);
    print_vert(e.edge_vert[1]);

    printf("\n");

    return 0;
}
