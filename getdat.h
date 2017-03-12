#ifndef __GET_DAT_H__
#define __GET_DAT_H__

#include "meta.h"
#include <stdio.h>
#include <stdlib.h>

#define IN_DATA "data/input/m100.off"

int get_meta(FILE *in);
int get_data(FILE *in);
int search_same_vert(Vert vertix, Vert *Array, int size);
int search_same_edge(Edge edge, Edge *Array, int size);
int comp_vert(Vert v1, Vert v2);
int vert_to_vert(Vert *v1, Vert v2);
int print_vert(Vert v);
int print_edge(Edge e);
int comp_edges(Edge e1, Edge e2);
int read_file(char *filename);

#endif
