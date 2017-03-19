#include "getdat.h"
#include "putdat.h"
#include "cmrlib.h"
#include "meta.h"
#include <omp.h>
#include <stdio.h>

int make_base(void);
int one_file(void);

int main(void)
{
    int n;
    printf("\n----------------Control of mesh resolution----------------\n\n");

    one_file();
    //make_base();

    printf("\n----------------------------------------------------------\n\n");

    return 0;
}

int make_base(void)
{
    int i, j;
    char in_buff[F_NAME_LEN];
    char out_buff[F_NAME_LEN];
    char buff[STR_LEN];

    open_info(OUT_INFODATA);

    for(i = 0; i < 17; ++i)
    {
        for(j = 0; j < 100; ++j)
        {

            sprintf(in_buff, "%s%d/m%d/m%d.off", DEF_IN_PATH, i, i * 100 + j, i * 100 + j);
            sprintf(out_buff, "%sm%d.off", DEF_OUT_PATH, i * 100 + j);
            sprintf(buff, "Processing file #%d\n", i*100 + j);

            if(read_file(in_buff))
            {
                printf("Too many edges!\n");
                fprintf(out_m, "File m%d.off\nToo many edges!\n", i * 100 + j);
                copy_file(in_buff, out_buff);
                continue;
            }

            if(print_info(buff) < (DEF_DES_RESOL + (DEF_DEVIATION / 2)))
            {
                printf("Resolution correct!\n\n");
                fprintf(out_m, "File m%d.off\nResolution correct!\n", i * 100 + j);
                copy_file(in_buff, out_buff);
                continue;
            }


            if(mesh_resol_control(DEF_DES_RESOL, DEF_DEVIATION))
            {
                printf("Can't change resolution!\n\n");
                fprintf(out_m, "File m%d.off\nCan't change resolution!\n", i * 100 + j);
                copy_file(in_buff, out_buff);
                continue;
            }

            write_file(out_buff);
        }
    }

    return 0;
}

int one_file(void)
{
    open_info(OUT_INFODATA);

    if(read_file(IN_DATA))
    {
        printf("Too many edges!\n");
        fprintf(out_m, "File %s\nToo many edges!\n", IN_DATA);
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
        fprintf(out_m, "File %s\nResolution correct!\n", IN_DATA);
        copy_file(IN_DATA, OUT_DATA);
        return 0;
    }

    if(mesh_resol_control(DEF_DES_RESOL, DEF_DEVIATION))
    {
        printf("Can't change resolution!\n");
        fprintf(out_m, "File %s\nCan't change resolution!\n", IN_DATA);
        copy_file(IN_DATA, OUT_DATA);
        return 1;
    }
    print_info("After algo:\n");

    write_file(OUT_DATA);

    return 0;
}
