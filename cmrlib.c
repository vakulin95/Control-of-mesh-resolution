#include "cmrlib.h"

int mesh_resol_control(float res, float dev)
{
    int i;
    float up_b, low_b;

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
            if(EdgeMass[i].length < low_b)
            {
                //printf("edge_collapse(%d)\n", i);
                edge_collapse(i);
            }
        }
        i++;
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
        return 1;
    }

    D = edge_diamond(ind);
    i = 0;
    while(i < 4 && D.vert[i].x != -1)
    {
        add_edge(D.vert[i], mid, ed_num + i);
        i++;
    }
    ed_num += i;
    EdgeMass[ed_num].sw = 0;

    EdgeMass[ind].sw = 0;

    return 0;
}

Diamond edge_diamond(int ind)
{
    int i, j, I, J, t;
    Vert v;
    Diamond Y;

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
        Y.vert[2].x = -1;
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
        Y.vert[3].x = -1;
    }

    ret:
    return Y;
}

//----------------------------------------------------------------------//

int edge_collapse(int ind)
{
    int i;
    Star S;
    Vert mid = calc_ed_midp(EdgeMass[ind]);

    if(!(EdgeMass[ind].sw))
    {
        printf("Trying to collapse delited edge!\n");
        getchar();
        return 1;
    }
    EdgeMass[ind].sw = 0;

    S  = edge_star(ind);
    for(i = 0; i < S.length; ++i)
    {
        //printf("%d\n", ed_num);
        add_edge(mid, S.vert[i], ed_num);
        ed_num++;
    }
    EdgeMass[ed_num].sw = 0;

    return 0;
}

Star edge_star(int ind)
{
    int i, j;
    Star Y;

    for(i = 0, j = 0; i < ed_num; ++i)
    {
        //printf("%d\n", j);
        if(EdgeMass[i].sw)
        {
            if(comp_vert(&(EdgeMass[ind].edge_vert[0]), &(EdgeMass[i].edge_vert[0]))
            || comp_vert(&(EdgeMass[ind].edge_vert[1]), &(EdgeMass[i].edge_vert[0])))
            {
                EdgeMass[i].sw = 0;
                if(!search_same_vert(EdgeMass[i].edge_vert[1], Y.vert, j) && j < DEF_SV_MASS_SIZE)
                {
                    vert_to_vert(&(Y.vert[j]), &(EdgeMass[i].edge_vert[1]));
                    j++;
                }
                else if(j >= DEF_SV_MASS_SIZE)
                {
                    printf("ERROR!: Out of star.vert[DEF_SV_MASS_SIZE]\n");
                    getchar();
                    goto ret;
                }
            }
            else if(comp_vert(&(EdgeMass[ind].edge_vert[0]), &(EdgeMass[i].edge_vert[1]))
                 || comp_vert(&(EdgeMass[ind].edge_vert[1]), &(EdgeMass[i].edge_vert[1])))
            {
                EdgeMass[i].sw = 0;
                if(!search_same_vert(EdgeMass[i].edge_vert[0], Y.vert, j) && j < DEF_SV_MASS_SIZE)
                {
                    vert_to_vert(&(Y.vert[j]), &(EdgeMass[i].edge_vert[0]));
                    j++;
                }
                else if(j >= DEF_SV_MASS_SIZE)
                {
                    printf("ERROR!: Out of star.vert[DEF_SV_MASS_SIZE]\n");
                    getchar();
                    goto ret;
                }
            }
        }
    }

    ret:

    Y.length = j;

    return Y;
}
