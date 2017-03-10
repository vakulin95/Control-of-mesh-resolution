#include "getdat.h"
#include "putdat.h"
#include "meta.h"
#include <stdio.h>

int main()
{
    int i, len;

    len = read_file(IN_DATA);

    if(len >= N)
        printf("\nMass is full: %d\n", len);

    write_file(OUT_DATA, len);

    return 0;
}
