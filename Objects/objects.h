#ifndef OBJECTS_H
#define OBJECTS_H

#include "vector.h"

typedef struct s_sphere
{
    char *id;
    t_vector center;
    double diameter;
    int *rgb;
} t_sphere;

typedef struct s_plane
{
    char *id;
    t_vector point;
    t_vector normalized;
    int *rgb;
} t_plane;

typedef struct s_cylinder
{
    char *id;
    t_vector center;
    t_vector normalized;
    double diameter;
    double height;
    int *rgb;
} t_cylinder;

#endif