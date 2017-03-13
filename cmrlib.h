#ifndef __CMRLIB_H__
#define __CMRLIB_H__

#include "meta.h"
#include "evlib.h"
#include "getdat.h"
#include <stdio.h>

int mesh_resol_control(float res, float dev);
int edge_split(int ind);
Diamond edge_diamond(int ind);

#endif
