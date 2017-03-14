#include "putdat.h"

int write_file(char *filename)
{
    int i;

    FILE *out;

    printf("write_file()\n");

    if(!(out = fopen(filename, "w")))
    {
        printf("ERROR!: write_file()\n");
        getchar();
        return -1;
    }

    prep_data();

    printf("Writing out file\n");
    fprintf(out, "%s\n%d %d %d\n", meta.format, meta.num_of_vert, meta.num_of_faces, meta.num_of_edges);

    for(i = 0; i < meta.num_of_vert; ++i)
    {
        fprintf(out, "%f %f %f\n", out_vert[i].x, out_vert[i].y, out_vert[i].z);
    }
    for(i = 0; i < meta.num_of_faces; ++i)
    {
        fprintf(out, "3 %d %d %d\n", out_face[i][0], out_face[i][1], out_face[i][2]);
    }

    //printf("Writing file\n");
    fclose(out);
    return 0;
}

int prep_data(void)
{
    int i;

    meta.num_of_vert = prep_vert_mass();
    meta.num_of_faces = prep_face_mass();

    return 0;
}

// Заполнить массив out_vert вершинами для записи в файл
int prep_vert_mass(void)
{
    int i, j;

    for(i = 0, j = 0; i < ed_num; ++i)
    {
        if(EdgeMass[i].sw)
        {
            if(!search_same_vert(EdgeMass[i].edge_vert[0], out_vert, j))
            {
                vert_to_vert(&(out_vert[j]), EdgeMass[i].edge_vert[0]);
                ++j;
            }
            if(!search_same_vert(EdgeMass[i].edge_vert[1], out_vert, j))
            {
                vert_to_vert(&(out_vert[j]), EdgeMass[i].edge_vert[1]);
                ++j;
            }
        }
    }

    return j;
}

// Заполнить массив out_face номерами точек из массива out_vert
int prep_face_mass(void)
{
    printf("prep_face_mass(void)\n");
    int i, j;
    Face F;

    for(i = 0, j = 0; i < ed_num; ++i)
    {
        //printf("%d ", i);
        if(EdgeMass[i].sw)
        {
            F = search_face(i, 0);
            if(F.vert[2].x != -1)
            {
                out_face[j][0] = search_ind_vert(&(F.vert[0]), out_vert, meta.num_of_vert);
                out_face[j][1] = search_ind_vert(&(F.vert[1]), out_vert, meta.num_of_vert);
                out_face[j][2] = search_ind_vert(&(F.vert[2]), out_vert, meta.num_of_vert);
                j++;
            }

            F = search_face(i, 1);
            if(F.vert[2].x != -1)
            {
                out_face[j][0] = search_ind_vert(&(F.vert[0]), out_vert, meta.num_of_vert);
                out_face[j][1] = search_ind_vert(&(F.vert[1]), out_vert, meta.num_of_vert);
                out_face[j][2] = search_ind_vert(&(F.vert[2]), out_vert, meta.num_of_vert);
                j++;
            }
            EdgeMass[i].sw = 0;
        }
    }

    return j;
}

// Найти треугольник в массиве EdgeMass
// Параметр num определяет номер треугольника по счету который нужно найти для ребра
// из массива. При num = 0 функция вернет первый треугольник, при всех остальных num - второй
Face search_face(int ind, int num)
{
    int i, j, fl;
    Face Y;

    vert_to_vert(&(Y.vert[0]), EdgeMass[ind].edge_vert[0]);
    vert_to_vert(&(Y.vert[1]), EdgeMass[ind].edge_vert[1]);
    Y.vert[2].x = -1.0;

    fl = 0;
    for(i = 0; i < ind; ++i)
    {
        if(EdgeMass[i].sw == 1)
        {
            for(j = i + 1; j < ed_num; ++j)
            {
                if(EdgeMass[j].sw == 1)
                {
                    if(j != ind)
                    {
                        if(is_face(&(EdgeMass[ind]), &(EdgeMass[i]), &(EdgeMass[j])))
                        {
                            if(!num || fl)
                            {
                                vert_to_vert(&(Y.vert[2]), comm_vert(&(EdgeMass[i]), &(EdgeMass[j])));
                                goto ret;
                            }
                            fl = 1;
                        }
                    }
                }
            }
        }
    }
    for(i = ind + 1; i < ed_num; ++i)
    {
        if(EdgeMass[i].sw == 1)
        {
            for(j = i + 1; j < ed_num; ++j)
            {
                if(EdgeMass[j].sw == 1)
                {
                    if(j != ind)
                    {
                        if(is_face(&(EdgeMass[ind]), &(EdgeMass[i]), &(EdgeMass[j])))
                        {
                            if(!num || fl)
                            {
                                vert_to_vert(&(Y.vert[2]), comm_vert(&(EdgeMass[i]), &(EdgeMass[j])));
                                goto ret;
                            }
                            fl = 1;
                        }
                    }
                }
            }
        }
    }

ret:
    return Y;
}

//--------------------------------------------------------------------------

// Открыть info.dat файл
int open_info(char *filename, char *filename_m)
{
    if(!(out_m = fopen(filename_m, "w")))
    {
        printf("ERROR!: write_meta()\n");
        getchar();
        return -1;
    }

    return 0;
}

// Напечатать в файл информацию о входном файле
int write_inp_info(char *filename)
{
    fprintf(out_m, "Name:\t%s\n\n", filename);
    fprintf(out_m, "Format:\t%s\nVert:\t%d\nFaces:\t%d\nEdges:\t%d\n\n",
            meta.format, meta.num_of_vert, meta.num_of_faces, meta.num_of_edges);

    if(same_vert)
    {
        fprintf(out_m, "Number of same vertices:\t%d\n", same_vert);
    }
    else
    {
        fprintf(out_m, "No same vertices!\n");
    }

    fprintf(out_m, "\n----------------------------------------------------------\n");
    return 0;
}

// Напечатать в файл массив EdgeMass
int write_temp(FILE *t_out, char *filename)
{
    int i, count_sw;
    float max, min;

    max = EdgeMass[0].length;
    min = EdgeMass[0].length;
    count_sw = 0;
    for(i = 0; i < ed_num; i++)
    {
        if(EdgeMass[i].sw)
        {
            count_sw++;
            if(EdgeMass[i].length > max)
            {
                max = EdgeMass[i].length;
            }
            if(EdgeMass[i].length < min)
            {
                min = EdgeMass[i].length;
            }
        }
    }
    fprintf(t_out, "\nEdgeMass size:\t%d\nNum of valid edges:\t%d\n\n", ed_num, count_sw);
    fprintf(t_out, "max len:\t%f\nmin len:\t%f\n", max, min);
    fprintf(out_m, "\n----------------------------------------------------------\n");

    // for(i = 0; i < ed_num; ++i)
    // {
    //     fprint_edge(t_out, EdgeMass[i]);
    // }

    return 0;
}

//--------------------------------------------------------------------------

// Напечатать в консоль информацию о EdgeMass с некоторым заголовком
int print_info(char *title)
{
    int i, count_sw;
    float max, min;

    max = EdgeMass[0].length;
    min = EdgeMass[0].length;
    count_sw = 0;
    for(i = 0; i < ed_num; i++)
    {
        if(EdgeMass[i].sw)
        {
            count_sw++;
            if(EdgeMass[i].length > max)
            {
                max = EdgeMass[i].length;
            }
            if(EdgeMass[i].length < min)
            {
                min = EdgeMass[i].length;
            }
        }
    }
    printf("\n%s\n", title);
    printf("EdgeMass size:\t\t%d\nNum of valid edges:\t%d\n\n", ed_num, count_sw);
    printf("max len:\t%f\nmin len:\t%f\n", max, min);

    return 0;
}
