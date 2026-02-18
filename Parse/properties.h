#ifndef PROPERTIES_H
#define PROPERTIES_H

#include "vector.h"

typedef struct s_ambient
{
    char *id;
    double light_ratio;
    int *rgb;
} t_ambient;

typedef struct s_camera
{
    char *id;
    t_vector viewpoint;
    t_vector orientation;
    double fov;
    // Campos adicionales para viewport
    t_vector up;
    t_vector right;
    double wview;
    double hview;
} t_camera;

typedef struct s_light
{
    char *id;
    t_vector light_point;
    double brightness;
    int *rgb;
} t_light;

#endif