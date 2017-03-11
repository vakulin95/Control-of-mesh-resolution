#ifndef __GET_DAT_H__
#define __GET_DAT_H__

#include "meta.h"
#include <stdio.h>
#include <stdlib.h>

#define IN_DATA "data/input/m100.off"

int get_meta(FILE *in);
int get_data(FILE *in);
int search_same_vert(Vert vertix, Vert *Array, int size);
int read_file(char *filename);

#endif
