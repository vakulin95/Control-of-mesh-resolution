#include "getdat.h"
#include "putdat.h"
#include "meta.h"
#include <stdio.h>

int main()
{
    printf("\n----------------Control of mesh resolution----------------\n\n");

    open_info(IN_DATA, OUT_INFODATA);
    read_file(IN_DATA);

    //write_file(IN_DATA);

    //getchar();
    return 0;
}
