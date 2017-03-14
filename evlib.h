#ifndef __EVLIB_H__
#define __EVLIB_H__

#include "meta.h"
#include <stdio.h>

int search_same_vert(Vert vertix, Vert *Array, int size);
int search_ind_vert(Vert vertix, Vert *Array, int size);
int comp_vert(Vert v1, Vert v2);
int vert_to_vert(Vert *v1, Vert v2);
int print_vert(Vert v);
int fprint_vert(FILE *out, Vert v);

int comp_edges(Edge e1, Edge e2);
int search_same_edge(Edge edge, Edge *Array, int size);
int print_edge(Edge e);
int fprint_edge(FILE *out, Edge e);
Vert calc_ed_midp(Edge e);
int edge_to_edge(Edge *e1, Edge e2);

int is_face(Edge e1, Edge e2, Edge e3);
int face_to_face(Face *f1, Face f2);
int comp_faces(Face f1, Face f2);
int search_same_face(Face f, Face *Array, int size);
Vert comm_vert(Edge e1, Edge e2);

#endif
