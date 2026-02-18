#ifndef OBJECTS_H
#define OBJECTS_H

#include "vector.h"

struct typedef s_sphere
{
    char *id;
    t_vector center;
    int diameter;
    t_vector *rgb;
} t_sphere;

struct typedef s_plane
{
    char *id;
    t_vector point;
    t_vector normalized;
    t_vector *rgb;
} t_plane;

struct typedef s_cylinder
{
    char *id;
    t_vector center;
    t_vector normalized;
    int diameter;
    int height;
    t_vector *rgb;
} t_cylinder;