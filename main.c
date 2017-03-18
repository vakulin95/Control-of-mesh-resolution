#include "getdat.h"
#include "putdat.h"
#include "cmrlib.h"
#include "meta.h"
#include <stdio.h>

int main()
{
    printf("\n----------------Control of mesh resolution----------------\n\n");

    read_file(IN_DATA);

    print_info("Before algo:\n");
    mesh_resol_control(DEF_DES_RESOL, DEF_DEVIATION);
    print_info("After algo:\n");

    write_file(OUT_DATA);

    printf("\n----------------------------------------------------------\n\n");
    //getchar();
    return 0;
}
