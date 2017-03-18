#ifndef __META_H__
#define __META_H__

#define F_FORMAT_LEN            10
#define F_NAME_LEN              50
#define DEF_IN_PATH             "/usr/home/artyom/db/"
#define DEF_OUT_PATH            "/usr/home/artyom/mc_db/"
#define DEF_SV_MASS_SIZE        50
#define DEF_EDGE_MASS_SIZE      10000000   // Размер массива ребер
#define DEF_DES_RESOL           0.07
#define DEF_DEVIATION           0.06

typedef struct obj_meta ObjMeta;
typedef struct vert Vert;
typedef struct edge Edge;
typedef struct diamond Diamond;
typedef struct star Star;
typedef struct face Face;

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

struct face
{
    Vert vert[3];
    Edge edge[3];
};

struct diamond
{
    Vert vert[4];
    //Face face[2];
};

struct star
{
    int length;
    Vert vert[DEF_SV_MASS_SIZE];
};

ObjMeta meta;   // Структура для метаданных
int same_vert;  // Количество одинаковых вершин во входном файле
int ed_num;     // Количество ребер в массиве EdgeMass
Edge EdgeMass[DEF_EDGE_MASS_SIZE];

#endif
