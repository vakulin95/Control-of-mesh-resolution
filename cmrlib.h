#ifndef __CMRLIB_H__
#define __CMRLIB_H__

#include "meta.h"
#include "evlib.h"
#include "getdat.h"
#include <stdio.h>

int mesh_resol_control(float res, float dev);
int edge_split(int ind);
Diamond edge_diamond(int ind);

int edge_collapse(int ind);
Star edge_star(int ind);
void calc_resol(void);
int init_algo_data(void);

float up_b, low_b;

#endif
