#ifndef __GET_DAT_H__
#define __GET_DAT_H__

#include "meta.h"
#include "evlib.h"
#include "putdat.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define IN_DATA "data/input/m1300.off"

int get_meta(FILE *in);
int get_data(FILE *in);
int add_edge(Vert v1, Vert v2, int ind);
int read_file(char *filename);

#endif
