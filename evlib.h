#ifndef __EVLIB_H__
#define __EVLIB_H__

#include "meta.h"
#include <stdio.h>

int search_same_vert(Vert vertix, Vert *Array, int size);
int comp_vert(Vert v1, Vert v2);
int vert_to_vert(Vert *v1, Vert v2);
int print_vert(Vert v);

int comp_edges(Edge e1, Edge e2);
int search_same_edge(Edge edge, Edge *Array, int size);
int print_edge(Edge e);

#endif
