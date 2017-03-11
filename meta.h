#ifndef __META_H__
#define __META_H__

#define F_FORMAT_LEN 10

typedef struct obj_meta ObjMeta;
typedef struct vert Vert;
typedef struct edge Edge;

struct obj_meta
{
    char format[F_FORMAT_LEN];
    int num_of_vert;
    int num_of_faces;
    int num_of_edges;
};

struct vert
{
    float x;
    float y;
    float z;
};

struct edge
{
    Vert edge_vert[2];
};

ObjMeta meta;   // Структура для метаданных
int same_vert;  // Количество одинаковых вершин во входном файле

#endif
