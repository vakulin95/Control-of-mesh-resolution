#ifndef __META_H__
#define __META_H__

#define IN_DATA                 "data/input/m100.off"
#define DEF_IN_PATH             "/home/artyom/db/"
#define DEF_OUT_PATH            "/home/artyom/mc_db/"

#define F_FORMAT_LEN            10
#define F_NAME_LEN              100
#define STR_LEN                 200
#define INFO_SIZE               2500

#define DEF_SV_MASS_SIZE        100                         // Количество вершин в EdgeStar
#define DEF_SE_MASS_SIZE        (DEF_SV_MASS_SIZE + 2)      // Количество ребер в EdgeStar
#define DEF_EDGE_MASS_SIZE      5000                        // Размер массива ребер

#define DEF_DES_RESOL           0.0475
#define DEF_DEVIATION           0.0850
#define DEF_DES_RESOL_2         0.1

// #define DEF_DES_RESOL           0.025
// #define DEF_DEVIATION           0.05
// #define DEF_DES_RESOL_2         0.1

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
    int val;
    Vert vert[4];
    //Face face[2];
};

struct star
{
    int length;
    int ed_length;
    Vert vert[DEF_SV_MASS_SIZE];
    Edge edge[DEF_SE_MASS_SIZE];
};

ObjMeta meta;   // Структура для метаданных
int same_vert;  // Количество одинаковых вершин во входном файле
int ed_num;     // Количество ребер в массиве EdgeMass
Edge EdgeMass[DEF_EDGE_MASS_SIZE];
float res_max, res_min;
int count_sw;

#endif
