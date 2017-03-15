#include "cmrlib.h"

int mesh_resol_control(float res, float dev)
{
    int i;
    float up_b, low_b;
    float max, min; // максимальное и минимальное значение длинн ребер в файле(для отладки)

    low_b = res - dev / 2;
    up_b = res + dev / 2;

    i = 0;
    while((i < ed_num) && (i < DEF_EDGE_MASS_SIZE))
    {
        if(EdgeMass[i].sw)
        {
            if(EdgeMass[i].length > up_b)
            {
                //printf("edge_split()\n");
                edge_split(i);
            }
            else if(EdgeMass[i].length < low_b)
            {
                // printf("edge_collapse()\n");
                // edge_collapse(EdgeMass[i]);
            }
            i++;
        }
    }

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
    }
    ed_num += 4;
    EdgeMass[ed_num].sw = 0;

    EdgeMass[ind].sw = 0;

    return 0;
}

Diamond edge_diamond(int ind)
{
    //printf("edge_diamond()\n");
    int i, j, I, J, t;
    Vert v;
    Diamond Y;

    //printf("edge_diamond()\n");

    if(!(EdgeMass[ind].sw))
    {
        printf("ERROR!: Trying to get edge_diamond from delited edge\n");
        getchar();
        goto ret;
    }

    vert_to_vert(&(Y.vert[0]), &(EdgeMass[ind].edge_vert[0]));
    vert_to_vert(&(Y.vert[1]), &(EdgeMass[ind].edge_vert[1]));

    I = -1;
    J = -1;
    t = 0;
    for(i = 0; i < ed_num; ++i)
    {
        if(EdgeMass[i].sw && i != ind)
        {
            for(j = i + 1; j < ed_num; ++j)
            {
                if(!(EdgeMass[j].sw) || j == ind)
                {
                    continue;
                }
                //printf("ind %d; i %d; j %d\n", ind, i, j);
                if(is_face(&(EdgeMass[ind]), &(EdgeMass[i]), &(EdgeMass[j])))
                {
                    //printf("1 %d %d %d\n", ind, i, j);
                    I = i;
                    J = j;
                    t = 1;
                    v = comm_vert(&(EdgeMass[i]), &(EdgeMass[j]));
                    vert_to_vert(&(Y.vert[2]), &v);

                    goto fl1;
                }
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

    for(; i < ed_num; ++i)
    {
        if(EdgeMass[i].sw)
        {
            for(j = i + 1; j < ed_num; ++j)
            {
                if((i == I && j == J) || i == ind || j == ind || !(EdgeMass[j].sw))
                {
                    continue;
                }
                //printf("ind %d; i %d; j %d\n", ind, i, j);
                if(is_face(&(EdgeMass[ind]), &(EdgeMass[i]), &(EdgeMass[j])))
                {
                    //printf("2 %d %d %d\n", ind, i, j);
                    v = comm_vert(&(EdgeMass[i]), &(EdgeMass[j]));
                    vert_to_vert(&(Y.vert[3]), &v);
                    t = 2;

                    goto fl2;
                }
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
