#include "main.h"
#include <mlx.h>
#include <stdlib.h>

static void free_spheres(t_sphere **list)
{
    t_sphere *cur;
    t_sphere *next;

    cur = list ? *list : NULL;
    while (cur)
    {
        next = cur->next;
        free(cur);
        cur = next;
    }
    if (list)
        *list = NULL;
}

static void free_planes(t_plane **list)
{
    t_plane *cur;
    t_plane *next;

    cur = list ? *list : NULL;
    while (cur)
    {
        next = cur->next;
        free(cur);
        cur = next;
    }
    if (list)
        *list = NULL;
}

static void free_cylinders(t_cylinder **list)
{
    t_cylinder *cur;
    t_cylinder *next;

    cur = list ? *list : NULL;
    while (cur)
    {
        next = cur->next;
        free(cur);
        cur = next;
    }
    if (list)
        *list = NULL;
}

void destroy_mlx(t_graph *mlx)
{
    if (!mlx)
        return;
    if (mlx->img)
    {
        mlx_destroy_image(mlx->mlx, mlx->img);
        mlx->img = NULL;
    }
    if (mlx->mlx_win)
    {
        mlx_destroy_window(mlx->mlx, mlx->mlx_win);
        mlx->mlx_win = NULL;
    }
#ifndef __APPLE__
    if (mlx->mlx)
    {
        mlx_destroy_display(mlx->mlx);
        free(mlx->mlx);
        mlx->mlx = NULL;
    }
#endif
}

void cleanup_scene(t_scene *scene)
{
    if (!scene)
        return;
    free_spheres(&scene->sphere);
    free_planes(&scene->plane);
    free_cylinders(&scene->cylinder);
    destroy_mlx(&scene->mlx);
}
