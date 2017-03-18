#include "getdat.h"
#include "putdat.h"
#include "cmrlib.h"
#include "meta.h"
#include <stdio.h>

int make_base(void);

int main()
{
    printf("\n----------------Control of mesh resolution----------------\n\n");

    read_file(IN_DATA);

    print_info("Before algo:\n");
    mesh_resol_control(DEF_DES_RESOL, DEF_DEVIATION);
    print_info("After algo:\n");

    write_file(OUT_DATA);

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
            read_file(buff);

            mesh_resol_control(DEF_DES_RESOL, DEF_DEVIATION);

            write_file(DEF_OUT_PATH);
        }
    }

    return 0;
}
