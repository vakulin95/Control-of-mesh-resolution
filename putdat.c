#include "putdat.h"

int write_file(char *filename)
{
    int i;

    FILE *out;

    prep_data();

    if(!(out = fopen(filename, "w")))
    {
        printf("ERROR!: write_file()\n");
        getchar();
        return -1;
    }

    fprintf(out, "%s\n%d %d %d\n", meta.format, meta.num_of_vert, meta.num_of_faces, meta.num_of_edges);

    for(i = 0; i < meta.num_of_vert; ++i)
    {
        fprintf(out, "%f %f %f\n", out_vert[i].x, out_vert[i].y, out_vert[i].z);
    }
    for(i = 0; i < meta.num_of_faces; ++i)
    {
        fprintf(out, "3 %d %d %d\n", out_face[i][0], out_face[i][1], out_face[i][2]);
    }

    fclose(out);
    clear_putdata();
    return 0;
}

int prep_data(void)
{
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
            if(j < (DEF_OUT_VERT - 2))
            {
                if(!search_same_vert(EdgeMass[i].edge_vert[0], out_vert, j))
                {
                    vert_to_vert(&(out_vert[j]), &(EdgeMass[i].edge_vert[0]));
                    ++j;
                }
                if(!search_same_vert(EdgeMass[i].edge_vert[1], out_vert, j))
                {
                    vert_to_vert(&(out_vert[j]), &(EdgeMass[i].edge_vert[1]));
                    ++j;
                }
            }
            else
            {
                printf("ERROR!: Out of out_vert[DEF_OUT_VERT]\n");
                getchar();
                return j;
            }
        }
    }

    return j;
}

// Заполнить массив out_face номерами точек из массива out_vert
int prep_face_mass(void)
{
    int i, j;
    Face F;

    for(i = 0, j = 0; i < ed_num; ++i)
    {
        if(EdgeMass[i].sw == 1)
        {
            if(j < (DEF_OUT_FACE - 2))
            {
                F = search_face(i, 0);
                if(F.vert[2].x != -1)
                {
                    out_face[j][0] = search_ind_vert(&(F.vert[0]), out_vert, meta.num_of_vert);
                    out_face[j][1] = search_ind_vert(&(F.vert[1]), out_vert, meta.num_of_vert);
                    out_face[j][2] = search_ind_vert(&(F.vert[2]), out_vert, meta.num_of_vert);
                    j++;
                }
                else
                {
                    //EdgeMass[i].sw = 0;
                    continue;
                }

                F = search_face(i, 1);
                if(F.vert[2].x != -1)
                {
                    out_face[j][0] = search_ind_vert(&(F.vert[0]), out_vert, meta.num_of_vert);
                    out_face[j][1] = search_ind_vert(&(F.vert[1]), out_vert, meta.num_of_vert);
                    out_face[j][2] = search_ind_vert(&(F.vert[2]), out_vert, meta.num_of_vert);
                    j++;
                }
                //EdgeMass[i].sw = 0;
            }
            else
            {
                printf("ERROR!: Out of out_face[DEF_OUT_FACE][3]\n");
                getchar();
                return j;
            }
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
    Vert v;

    Y.vert[2].x = -1.0;

    fl = 0;
    for(i = ind + 1; i < ed_num; ++i)
    {
        if(EdgeMass[i].sw == 1)
        {
            for(j = i + 1; j < ed_num; ++j)
            {
                if(EdgeMass[j].sw == 1)
                {
                    if(is_face(&(EdgeMass[ind]), &(EdgeMass[i]), &(EdgeMass[j])) == 1)
                    {
                        if(!num || fl)
                        {
                            v = comm_vert(&(EdgeMass[i]), &(EdgeMass[j]));
                            vert_to_vert(&(Y.vert[2]), &v);
                            goto ret;
                        }
                        fl = 1;
                    }
                }
            }
        }
    }

    ret:

    if(Y.vert[2].x != -1.0)
    {
        vert_to_vert(&(Y.vert[0]), &(EdgeMass[ind].edge_vert[0]));
        vert_to_vert(&(Y.vert[1]), &(EdgeMass[ind].edge_vert[1]));
    }
    return Y;
}

int copy_file(char *in_filename, char *out_filename)
{
    int i;
    char buf[STR_LEN];

    FILE *in, *out;

    if(!(in = fopen(in_filename, "r")) || !(out = fopen(out_filename, "w")))
    {
        printf("ERROR!: copy_file()\n");
        getchar();
        return -1;
    }

    while(fgets(buf, 100, in) != NULL)
    {
        fprintf(out, "%s", buf);
    }

    return 0;
}

int clear_putdata(void)
{
    int i;

    for(i = 0; i < meta.num_of_vert; ++i)
    {
        out_vert[i].x = out_vert[i].y = out_vert[i].z = -1.0;
    }
    for(i = 0; i < meta.num_of_faces; ++i)
    {
        out_face[i][0] = out_face[i][1] = out_face[i][2] = -1;
    }

    return 0;
}

//--------------------------------------------------------------------------

// Напечатать inf.dat файл
int write_inp_info(char info_text[INFO_SIZE][STR_LEN])
{
    int i;
    char info_buff[F_NAME_LEN];
    FILE *out_m;

    sprintf(info_buff, "%s#info.dat", DEF_OUT_PATH);
    if(!(out_m = fopen(info_buff, "w")))
    {
        printf("ERROR!: write_meta()\n");
        getchar();
        return -1;
    }
    fprintf(out_m, "\n---------------------------------Control of mesh resolution---------------------------------\n\n");
    fprintf(out_m,
    "DEF_IN_PATH\t\t\t%s\nDEF_OUT_PATH\t\t%s\nDEF_EDGE_MASS_SIZE\t%d\n\nDEF_DES_RESOL\t\t%.4f\nDEF_DEVIATION\t\t%.4f\nDEF_DES_RESOL_2\t\t%.4f\n",
    DEF_IN_PATH, DEF_OUT_PATH, DEF_EDGE_MASS_SIZE,
    DEF_DES_RESOL, DEF_DEVIATION, DEF_DES_RESOL_2);
    fprintf(out_m, "\n--------------------------------------------------------------------------------------------\n\n");

    for(i = 0; i < INFO_SIZE; ++i)
    {
        fprintf(out_m, "%s\n", info_text[i]);
    }

    fclose(out_m);
    return 0;
}

//--------------------------------------------------------------------------

// Напечатать в консоль информацию о EdgeMass с некоторым заголовком
float print_info(char *title)
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
    printf("EdgeMass size:\t%d\nVal edges:\t%d\n\n", ed_num, count_sw);
    printf("max len:\t%f\nmin len:\t%f\n", max, min);

    return max;
}
