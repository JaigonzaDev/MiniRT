#ifndef MAIN_H
#define MAIN_H

#include "graph.h"
#include "vector.h"
#include "objects.h"

typedef struct s_scene
{
    t_graph mlx;

    t_camera camera;
    t_ambient ambient;
    t_light light;

    t_cylinder cylinder;
    t_sphere sphere;
    t_plabe plane;
} t_scene;