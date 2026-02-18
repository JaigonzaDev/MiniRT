#ifndef PROPERTIES_H
#define PROPERTIES_H

#include "vector.h"

struct typedef s_ambient
{
    char *id;
    int light_ratio;
    t_vector *rgb;
} t_ambient;

struct typedef s_camera
{
    char *id;
    t_vector *viewpoint;
    t_vector *orientation;
    int fov;
} t_camera;

struct typedef s_light
{
    char *id;
    t_vector light_point;
    int *brightness;
    t_vector *rgb;
} t_light;