#ifndef __PUTDAT_H__
#define __PUTDAT_H__

#include "meta.h"
#include "evlib.h"
#include "cmrlib.h"
#include <stdio.h>

#define OUT_DATA            "data/output/out.off"
#define OUT_INFODATA        "data/output/#info.dat"
#define DEF_OUT_VERT        10000
#define DEF_OUT_FACE        10000

int write_file(char *filename);
int prep_data(void);
int prep_vert_mass(void);
int prep_face_mass(void);
Face search_face(int ind, int num);

int open_info(char *filename, char *filename_m);
int write_inp_info(char *filename);
int write_temp(char *title);

int print_info(char *title);

FILE *out_m;
Vert out_vert[DEF_OUT_VERT];
int out_face[DEF_OUT_FACE][3];

#endif
