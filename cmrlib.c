#include "cmrlib.h"

int mesh_resol_control(float res, float dev)
{
    int i;
    float up_b, low_b;
    float max, min; // максимальное и минимальное значение длинн ребер в файле(для отладки)

    low_b = res - dev / 2;
    up_b = res + dev / 2;

    i = 0;
    while((i < ed_num) || (i < DEF_EDGE_MASS_SIZE))
    {
        if(EdgeMass[i].sw && EdgeMass[i].length > up_b)
        {
            //printf("edge_split()\n");
            edge_split(i);
        }
        else if(EdgeMass[i].sw && EdgeMass[i].length < low_b)
        {
            // printf("edge_collapse()\n");
            // edge_collapse(EdgeMass[i]);
        }
        i++;
    }

    printf("\nEdges num: %d\n\n", ed_num);
    max = EdgeMass[0].length;
    min = EdgeMass[0].length;
    for(i = 0; i < ed_num; i++)
    {
        if(EdgeMass[i].sw && EdgeMass[i].length > max)
        {
            max = EdgeMass[i].length;
        }
        if(EdgeMass[i].sw && EdgeMass[i].length < min)
        {
            min = EdgeMass[i].length;
        }
    }
    printf("max len:\t%f\nmin len:\t%f\n\n", max, min);
    // for(i = ed_num - 5; i < ed_num; i++)
    // {
    //     print_edge(EdgeMass[i]);
    // }
    // printf("\n");

    return 0;
}

//----------------------------------------------------------------------//

int edge_split(int ind)
{
    int i;
    Vert mid = calc_ed_midp(EdgeMass[ind]);
    Diamond D;

    if(!(EdgeMass[ind].sw))
    {
        printf("Trying to split delited edge!\n");
        getchar();
    }

    D = edge_diamond(ind);
    for(i = 0; i < 4; ++i)
    {
        add_edge(D.vert[i], mid, ed_num + i);
        // vert_to_vert(&(EdgeMass[ed_num + i].edge_vert[0]), D.vert[i]);
        // vert_to_vert(&(EdgeMass[ed_num + i].edge_vert[1]), mid);
    }
    ed_num += 4;
    EdgeMass[ed_num].sw = -1;

    EdgeMass[ind].sw = 0;

    return 0;
}

Diamond edge_diamond(int ind)
{
    int i, j, I, J, t;
    Vert v1, v2;
    Diamond Y;

    //printf("edge_diamond()\n");

    if(!(EdgeMass[ind].sw))
    {
        printf("ERROR!: Trying to get edge_diamond from delited edge\n");
        getchar();
        goto ret;
    }

    vert_to_vert(&(v1), EdgeMass[ind].edge_vert[0]);
    vert_to_vert(&(v2), EdgeMass[ind].edge_vert[1]);

    vert_to_vert(&(Y.vert[0]), v1);
    vert_to_vert(&(Y.vert[1]), v2);

    I = -1;
    J = -1;
    t = 0;
    for(i = 0; i < ed_num; ++i)
    {
        for(j = i + 1; j < ed_num; ++j)
        {
            if(i == ind || j == ind || !(EdgeMass[i].sw) || !(EdgeMass[j].sw))
            {
                continue;
            }
            //printf("ind %d; i %d; j %d\n", ind, i, j);
            if(is_face(EdgeMass[ind], EdgeMass[i], EdgeMass[j]))
            {
                //printf("1 %d %d %d\n", ind, i, j);
                I = i;
                J = j;
                t = 1;
                vert_to_vert(&(Y.vert[2]), comm_vert(EdgeMass[i], EdgeMass[j]));

                edge_to_edge(&(Y.face[0].edge[0]), EdgeMass[ind]);
                edge_to_edge(&(Y.face[0].edge[1]), EdgeMass[i]);
                edge_to_edge(&(Y.face[0].edge[2]), EdgeMass[j]);

                goto fl1;
            }
        }
    }

fl1:

    if(!t)
    {
        printf("ERROR!: No faces was found in edge_diamond()\n");
        getchar();
        goto ret;
    }

    for(i = 0; i < ed_num; ++i)
    {
        for(j = i + 1; j < ed_num; ++j)
        {
            if((i == I && j == J) || i == ind || j == ind || !(EdgeMass[i].sw) || !(EdgeMass[j].sw))
            {
                continue;
            }
            //printf("ind %d; i %d; j %d\n", ind, i, j);
            if(is_face(EdgeMass[ind], EdgeMass[i], EdgeMass[j]))
            {
                //printf("2 %d %d %d\n", ind, i, j);
                vert_to_vert(&(Y.vert[3]), comm_vert(EdgeMass[i], EdgeMass[j]));
                t = 2;

                edge_to_edge(&(Y.face[1].edge[0]), EdgeMass[ind]);
                edge_to_edge(&(Y.face[1].edge[1]), EdgeMass[i]);
                edge_to_edge(&(Y.face[1].edge[2]), EdgeMass[j]);

                goto fl2;
            }
        }
    }

fl2:

    if(t != 2)
    {
        printf("ERROR!: No second face in edge_diamond()\n");
        getchar();
        goto ret;
    }

ret:
    //printf("edge_diamond() complete!\n");
    return Y;
}
