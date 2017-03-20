#include "getdat.h"
#include "putdat.h"
#include "cmrlib.h"
#include "meta.h"
#include <omp.h>
#include <stdio.h>
#include <string.h>

int make_base(int i_beg, int i_end);
int one_file(void);

int main(int argc, char *argv[])
{
    int I_beg, I_end;

    printf("\n----------------Control of mesh resolution----------------\n\n");

    if(argc == 2 && !strcmp(argv[1], "-b"))
    {
        printf("Select the folders to process [0 - 18]:\n");
        printf("Begin:\t");
        scanf("%d", &I_beg);
        printf("End:\t");
        scanf("%d", &I_end);

        make_base(I_beg, I_end);
    }
    else if(argc == 2 && !strcmp(argv[1], "-o"))
    {
        one_file();
    }
    else
    {
        printf("Invalid arguments in main()!\nTry:\n");
        printf("\t-o: to try algo with one file;\n\t-b: to make data base;");
    }

    printf("\n----------------------------------------------------------\n\n");

    return 0;
}

int make_base(int i_beg, int i_end)
{
    int i, j, j_end, s_inf;
    char in_buff[F_NAME_LEN];
    char out_buff[F_NAME_LEN];

    char info_text[INFO_SIZE][STR_LEN];

    for(i = i_beg, s_inf = 0; i < (i_end + 1); ++i)
    {
        if(i != 18)
        {
            j_end = 2;
        }
        else
        {
            j_end = 15;
        }
        for(j = 0; j < j_end; ++j)
        {
            init_algo_data();

            sprintf(in_buff, "%s%d/m%d/m%d.off", DEF_IN_PATH, i, i * 100 + j, i * 100 + j);
            sprintf(out_buff, "%sm%d.off", DEF_OUT_PATH, i * 100 + j);

            printf("Processing file #%d\n", i*100 + j);

            if(read_file(in_buff))
            {
                sprintf(info_text[s_inf++], "m%d.off: Too many edges", i * 100 + j);
                copy_file(in_buff, out_buff);
                continue;
            }

            calc_resol();
            if(res_max < (DEF_DES_RESOL + (DEF_DEVIATION / 2)))
            {
                sprintf(info_text[s_inf++], "m%d.off: Resolution correct", i * 100 + j);
                copy_file(in_buff, out_buff);
                continue;
            }

            if(mesh_resol_control(DEF_DES_RESOL, DEF_DEVIATION))
            {
                sprintf(info_text[s_inf++],
                "m%d.off: Mesh correction failed. Trying without edge_collapse() with max edge len: %.2f",
                i * 100 + j, 2 * DEF_DES_RESOL_2);

                init_algo_data();
                read_file(IN_DATA);
                if(mesh_resol_control(DEF_DES_RESOL_2, 2*DEF_DES_RESOL_2))
                {
                    sprintf(info_text[s_inf++], "m%d.off: Can't change resolution!\n", i * 100 + j);
                    copy_file(in_buff, out_buff);
                    continue;
                }
            }

            write_file(out_buff);
        }
    }
    write_inp_info(info_text);

    return 0;
}

int one_file(void)
{
    if(read_file(IN_DATA))
    {
        printf("Too many edges!\n");
        copy_file(IN_DATA, OUT_DATA);
        return 0;
    }

    printf("Name:\t\t%s\n", IN_DATA);
    printf("Format:\t\t%s\nvert:\t\t%d\nfaces:\t\t%d\nedges:\t\t%d\n\nmax edge len:\t%f\nmin edge len:\t%f\n",
            meta.format, meta.num_of_vert, meta.num_of_faces, meta.num_of_edges,
            DEF_DES_RESOL + (DEF_DEVIATION / 2), DEF_DES_RESOL - (DEF_DEVIATION / 2));

    if(print_info("Before algo:\n") < (DEF_DES_RESOL + (DEF_DEVIATION / 2)))
    {
        printf("Resolution correct!\n\n");
        copy_file(IN_DATA, OUT_DATA);
        return 0;
    }

    if(mesh_resol_control(DEF_DES_RESOL, DEF_DEVIATION)) // < try without collapse
    {
        printf("Mesh correction failed\nTrying without edge_collapse() with max edge len: %f\n", 2 * DEF_DES_RESOL_2);

        init_algo_data();
        read_file(IN_DATA);
        if(mesh_resol_control(DEF_DES_RESOL_2, 2*DEF_DES_RESOL_2))
        {
            printf("Can't change resolution!\n\n");
            copy_file(IN_DATA, OUT_DATA);
            return 0;
        }
    }
    print_info("After algo:\n");

    write_file(OUT_DATA);

    return 0;
}
