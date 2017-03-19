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

int search_ind_vert(Vert *vertix, Vert *Array, int size)
{
    int i;
    int Y = -1;

    for(i = 0; i < size; ++i)
    {
        if(vertix->x == Array[i].x && vertix->y == Array[i].y && vertix->z == Array[i].z)
        {
            Y = i;
            goto ret;
        }
    }

    // if(Y == -1)
    // {
    //     printf("ERROR!: No vert was found in mass! search_ind_vert()\n");
    //     getchar();
    // }

ret:
    return Y;
}

// Сравнить две точки

int comp_vert(Vert *v1, Vert *v2)
{
    int Y = 0;

    if(v1->x == v2->x && v1->y == v2->y && v1->z == v2->z)
    {
        Y = 1;
    }

    return Y;
}

// Присвоить одну точку другой
int vert_to_vert(Vert *v1, Vert *v2)
{
    v1->x = v2->x;
    v1->y = v2->y;
    v1->z = v2->z;

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
int comp_edges(Edge *e1, Edge *e2)
{
    int Y = 0;

    if(e1->sw && e2->sw)
    {
        if(comp_vert(&(e1->edge_vert[0]), &(e2->edge_vert[0]))
        && comp_vert(&(e1->edge_vert[1]), &(e2->edge_vert[1])))
        {
            Y = 1;
            goto ret;
        }
        else if(comp_vert(&(e1->edge_vert[1]), &(e2->edge_vert[0]))
             && comp_vert(&(e1->edge_vert[0]), &(e2->edge_vert[1])))
        {
            Y = 1;
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
        printf("Trying to compare delited edge!\n");
        getchar();
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
        if(comp_edges(&edge, &(Array[i])))
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

// Вычислить среднюю точку ребра
Vert calc_ed_midp(Edge e)
{
    Vert out;

    out.x = (e.edge_vert[0].x + e.edge_vert[1].x) / 2;
    out.y = (e.edge_vert[0].y + e.edge_vert[1].y) / 2;
    out.z = (e.edge_vert[0].z + e.edge_vert[1].z) / 2;

    return out;
}

// Присвоить одно ребро другому
int edge_to_edge(Edge *e1, Edge e2)
{
    vert_to_vert(&(e1->edge_vert[0]), &(e2.edge_vert[0]));
    vert_to_vert(&(e1->edge_vert[1]), &(e2.edge_vert[1]));

    return 0;
}

//-----------------------------------------------------------------------------//

// Проверка являются ли три ребра треугольником
int is_face(Edge *e1, Edge *e2, Edge *e3)
{
    int Y = 0;

    if(comp_edges(e1, e2) || comp_edges(e1, e3) || comp_edges(e2, e3))
    {
        printf("ERROR!: Invalid value in is_face()\n");
        // print_edge(*e1);
        // print_edge(*e2);
        // print_edge(*e3);
        // getchar();
        Y = -1;
        goto ret;
    }

    if(comp_vert(&(e1->edge_vert[0]), &(e2->edge_vert[0])))
    {
        if((comp_vert(&(e1->edge_vert[1]), &(e3->edge_vert[0])) && comp_vert(&(e2->edge_vert[1]), &(e3->edge_vert[1])))
        || (comp_vert(&(e1->edge_vert[1]), &(e3->edge_vert[1])) && comp_vert(&(e2->edge_vert[1]), &(e3->edge_vert[0]))))
        {
            Y = 1;
            goto ret;
        }
    }

    if(comp_vert(&(e1->edge_vert[1]), &(e2->edge_vert[0])))
    {
        if((comp_vert(&(e1->edge_vert[0]), &(e3->edge_vert[0])) && comp_vert(&(e2->edge_vert[1]), &(e3->edge_vert[1])))
        || (comp_vert(&(e1->edge_vert[0]), &(e3->edge_vert[1])) && comp_vert(&(e2->edge_vert[1]), &(e3->edge_vert[0]))))
        {
            Y = 1;
            goto ret;
        }
    }

    if(comp_vert(&(e1->edge_vert[0]), &(e2->edge_vert[1])))
    {
        if((comp_vert(&(e1->edge_vert[1]), &(e3->edge_vert[0])) && comp_vert(&(e2->edge_vert[0]), &(e3->edge_vert[1])))
        || (comp_vert(&(e1->edge_vert[1]), &(e3->edge_vert[1])) && comp_vert(&(e2->edge_vert[0]), &(e3->edge_vert[0]))))
        {
            Y = 1;
            goto ret;
        }
    }

    if(comp_vert(&(e1->edge_vert[1]), &(e2->edge_vert[1])))
    {
        if((comp_vert(&(e1->edge_vert[0]), &(e3->edge_vert[0])) && comp_vert(&(e2->edge_vert[0]), &(e3->edge_vert[1])))
        || (comp_vert(&(e1->edge_vert[0]), &(e3->edge_vert[1])) && comp_vert(&(e2->edge_vert[0]), &(e3->edge_vert[0]))))
        {
            Y = 1;
            goto ret;
        }
    }

ret:
    return Y;
}

// Найти общую вершину двух ребер
Vert comm_vert(Edge *e1, Edge *e2)
{
    Vert Y;

    if(comp_vert(&(e1->edge_vert[0]), &(e2->edge_vert[0])))
    {
        vert_to_vert(&Y, &(e1->edge_vert[0]));
        goto ret;
    }
    if(comp_vert(&(e1->edge_vert[0]), &(e2->edge_vert[1])))
    {
        vert_to_vert(&Y, &(e1->edge_vert[0]));
        goto ret;
    }
    if(comp_vert(&(e1->edge_vert[1]), &(e2->edge_vert[0])))
    {
        vert_to_vert(&Y, &(e1->edge_vert[1]));
        goto ret;
    }
    if(comp_vert(&(e1->edge_vert[1]), &(e2->edge_vert[1])))
    {
        vert_to_vert(&Y, &(e1->edge_vert[1]));
        goto ret;
    }

    printf("There no common vertices in comm_vert()\n");
    getchar();

ret:
    return Y;
}
