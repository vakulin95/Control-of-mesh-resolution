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

    printf("\n----------------------------------------------------------\n\n");

    return 0;
}

int make_base(void)
{
    int i, j;
    char buff[F_NAME_LEN];

    for(i = 0; i < 17; ++i)
    {
        for(j = 0; j < 100; ++j)
        {
            printf("Processing file #%d\n", i*100 + j);
            sprintf(buff, "%s%d/m%d.off", DEF_IN_PATH, i, j);

            if(read_file(buff) < up_b)
            {
                printf("Resolution correct!\n\n");
                fprintf(out_m, "File %s\nResolution correct!\n", IN_DATA);
                continue;
            }

            if(mesh_resol_control(DEF_DES_RESOL, DEF_DEVIATION))
            {
                printf("Can't change resolution!\n\n");
                fprintf(out_m, "File %s\nCan't change resolution!\n", IN_DATA);
                continue;
            }

            write_file(DEF_OUT_PATH);
        }
    }

    return 0;
}

int one_file(void)
{
    open_info(IN_DATA, OUT_INFODATA);

    if(read_file(IN_DATA) < up_b)
    {
        printf("Resolution correct!\n");
        fprintf(out_m, "File %s\nResolution correct!\n", IN_DATA);
        return 0;
    }

    printf("Name:\t\t%s\n", IN_DATA);
    printf("Format:\t\t%s\nvert:\t\t%d\nfaces:\t\t%d\nedges:\t\t%d\n\nmax edge len:\t%f\nmin edge len:\t%f\n",
            meta.format, meta.num_of_vert, meta.num_of_faces, meta.num_of_edges,
            up_b, low_b);

    print_info("Before algo:\n");
    if(mesh_resol_control(DEF_DES_RESOL, DEF_DEVIATION))
    {
        printf("Can't change resolution!\n");
        fprintf(out_m, "File %s\nCan't change resolution!\n", IN_DATA);
        return 1;
    }
    print_info("After algo:\n");

    write_file(OUT_DATA);

    return 0;
}
