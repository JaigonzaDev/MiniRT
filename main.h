#ifndef MAIN_H
#define MAIN_H

#include "Graph/graph.h"
#include "Vector/vector.h"
#include "Objects/objects.h"
#include "Parse/properties.h"

typedef struct s_scene
{
    t_graph mlx;

    t_camera camera;
    t_ambient ambient;
    t_light light;

    t_cylinder *cylinder;
    t_sphere *sphere;
    t_plane *plane;
} t_scene;

#include "render/render.h"

void    cleanup_scene(t_scene *scene);
void    destroy_mlx(t_graph *mlx);

#endif