#include "getdat.h"
#include "putdat.h"
#include "cmrlib.h"
#include "meta.h"
#include <stdio.h>

int main()
{
    printf("\n----------------Control of mesh resolution----------------\n\n");

    // open_info(IN_DATA, OUT_INFODATA);

    read_file(IN_DATA);

    // write_inp_info(IN_DATA);
    // fprintf(out_m, "Raw data:\n");
    // write_temp(out_m, OUT_INFODATA);
    //
    print_info("Before algo:\n");
    mesh_resol_control(DEF_DES_RESOL, DEF_DEVIATION);
    print_info("After algo:\n");
    //
    // fprintf(out_m, "After mesh resolution control:\n");
    // write_temp(out_m, OUT_INFODATA);

    write_file(OUT_DATA);

    printf("\n----------------------------------------------------------\n\n");
    //getchar();
    return 0;
}
