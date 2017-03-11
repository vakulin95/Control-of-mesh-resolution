#ifndef __PUTDAT_H__
#define __PUTDAT_H__

#include "meta.h"
#include <stdio.h>

#define OUT_DATA "data/output/m100.off"
#define OUT_METADATA "data/output/meta.dat"

int write_meta(char *filename, char *filename_m);
int write_file(char *filename);

#endif
