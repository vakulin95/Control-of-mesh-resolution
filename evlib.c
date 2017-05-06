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
        //getchar();
        Y = 0;
        goto ret;
    }
ret:
    return Y;
}

// Сравнить два ребра не смотря на их валидность
int comp_edges_nosw(Edge *e1, Edge *e2)
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

// Поиск одинаковых ребер в массиве не смотря на валидность
// Если найдено, возврат индекса, иначе -1
int search_same_edge_nosw(Edge edge, Edge *Array, int size)
{
    int i;
    int Y = -1;

    for(i = 0; i < size; ++i)
    {
        if(comp_edges_nosw(&edge, &(Array[i])))
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

//Вычислить среднее проекций середины ребра на N плоскостей
Vert calc_edpp_on_plane(Edge e, Star s)
{
    int i, j;
    Vert Y, temp, N, midp;
    Edge te;
    float sum_x, sum_y, sum_z, offset, scal_pwo;

    midp = calc_ed_midp(e);
    sum_x = sum_y = sum_z = 0;
    for(i = 0; i < s.ed_length - 1; i++)
    {
        for(j = i + 1; j < s.ed_length; j++)
        {
            temp = comm_vert(&(s.edge[i]), &(s.edge[j]));
            if(temp.x != -1.0) // Если есть общая точка, найти третье ребро
            {
                //Определение третьего ребра для поиска
                if(!comp_vert(&(temp), &(s.edge[i].edge_vert[0])) && !comp_vert(&(temp), &(s.edge[j].edge_vert[0])))
                {
                    vert_to_vert(&(te.edge_vert[0]), &(s.edge[i].edge_vert[0]));
                    vert_to_vert(&(te.edge_vert[1]), &(s.edge[j].edge_vert[0]));
                }
                if(!comp_vert(&(temp), &(s.edge[i].edge_vert[0])) && !comp_vert(&(temp), &(s.edge[j].edge_vert[1])))
                {
                    vert_to_vert(&(te.edge_vert[0]), &(s.edge[i].edge_vert[0]));
                    vert_to_vert(&(te.edge_vert[1]), &(s.edge[j].edge_vert[1]));
                }
                if(!comp_vert(&(temp), &(s.edge[i].edge_vert[1])) && !comp_vert(&(temp), &(s.edge[j].edge_vert[0])))
                {
                    vert_to_vert(&(te.edge_vert[0]), &(s.edge[i].edge_vert[1]));
                    vert_to_vert(&(te.edge_vert[1]), &(s.edge[j].edge_vert[0]));
                }
                if(!comp_vert(&(temp), &(s.edge[i].edge_vert[1])) && !comp_vert(&(temp), &(s.edge[j].edge_vert[1])))
                {
                    vert_to_vert(&(te.edge_vert[0]), &(s.edge[i].edge_vert[1]));
                    vert_to_vert(&(te.edge_vert[1]), &(s.edge[j].edge_vert[1]));
                }

                if(search_same_edge_nosw(te, EdgeMass, ed_num) != -1)
                {
                    N = calc_normal(&temp, &(te.edge_vert[0]), &(te.edge_vert[1]));
                    offset = calc_offset(&temp, &midp, &N);

                    scal_pwo = N.x * midp.x + N.y * midp.y + N.z * midp.z + offset;
                    sum_x += scal_pwo * N.x;
                    sum_y += scal_pwo * N.y;
                    sum_z += scal_pwo * N.z;
                }
            }
        }
    }

    sum_x /= s.ed_length;
    sum_y /= s.ed_length;
    sum_z /= s.ed_length;

    Y.x = midp.x - sum_x;
    Y.y = midp.y - sum_y;
    Y.z = midp.z - sum_z;

    return Y;
}

//Вычислить нормаль к плоскости по трем точкам
Vert calc_normal(Vert *v1, Vert *v2, Vert *v3)
{
    Vert V, W, N;

    V.x = v2->x - v1->x;
    V.y = v2->y - v1->y;
    V.z = v2->z - v1->z;

    W.x = v3->x - v1->x;
    W.y = v3->y - v1->y;
    W.z = v3->z - v1->z;

    N.x = (V.y * W.z) - (V.z * W.y);
    N.y = (V.z * W.x) - (V.x * W.z);
    N.z = (V.x * W.y) - (V.y * W.x);

    return N;
}

// Вычислить расстояние от точки до плоскости
float calc_offset(Vert *v, Vert *x, Vert *N)
{
    float O, d;

    d = -(N->x * v->x + N->y * v->y + N->z * v->z);

    O = fabs(N->x * x->x + N->y * x->y + N->z * x->z + d) / sqrt(pow(N->x, 2) + pow(N->y, 2) + pow(N->z, 2));

    return O;
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
        //printf("ERROR!: Invalid value in is_face()\n");
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

    Y.x = Y.y = Y.z = -1.0;
    //printf("There no common vertices in comm_vert()\n");
    //getchar();

ret:
    return Y;
}
