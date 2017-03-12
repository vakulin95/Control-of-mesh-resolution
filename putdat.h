#ifndef __PUTDAT_H__
#define __PUTDAT_H__

#include "meta.h"
#include <stdio.h>

#define OUT_DATA "data/output/m100.off"
#define OUT_INFODATA "data/output/#info.dat"

FILE *out_m;

int open_info(char *filename, char *filename_m);
int inp_info(char *filename);
int write_file(char *filename);

#endif
