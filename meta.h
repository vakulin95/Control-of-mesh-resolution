#ifndef __META_H__
#define __META_H__

#define F_FORMAT_LEN 10

struct ObjMeta
{
    char format[F_FORMAT_LEN];
    int num_of_vert;
    int num_of_faces;
    int num_of_edges;
};

struct ObjMeta meta;

#endif
