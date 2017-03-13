#include "getdat.h"
#include "putdat.h"
#include "cmrlib.h"
#include "meta.h"
#include <stdio.h>

int main()
{
    printf("\n----------------Control of mesh resolution----------------\n\n");

    open_info(IN_DATA, OUT_INFODATA);
    read_file(IN_DATA);

    mesh_resol_control(DEF_DES_RESOL, DEF_DEVIATION);

    //write_file(IN_DATA);

    printf("\n----------------------------------------------------------\n\n");
    //getchar();
    return 0;
}
