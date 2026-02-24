#ifndef MAIN_H
#define MAIN_H

#include "graph/graph.h"
#include "vector/vector.h"
#include "objects/objects.h"
#include "parse/properties.h"

typedef struct s_scene
{
    t_graph mlx;

    t_camera camera;
    t_ambient ambient;
    t_light light;

    t_cylinder cylinder;
    t_sphere sphere;
    t_plane plane;
} t_scene;

#include "render/render.h"

#endif