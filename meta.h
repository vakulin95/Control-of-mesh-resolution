#ifndef __META_H__
#define __META_H__

#define F_FORMAT_LEN            10
#define DEF_EDGE_MASS_SIZE      10000000   // Размер массива ребер

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
    int sw;
    Vert edge_vert[2];
    float length;
};

ObjMeta meta;   // Структура для метаданных
int same_vert;  // Количество одинаковых вершин во входном файле
int ed_num;
Edge EdgeMass[DEF_EDGE_MASS_SIZE];

#endif
