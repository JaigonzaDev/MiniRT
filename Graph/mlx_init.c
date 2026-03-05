#include "graph.h"
#include "../main.h"
#include "../render/render.h"
#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>

int mlx_signals(int keycode, void *param)
{
    t_scene *scene;

    scene = (t_scene *)param;
#ifdef __APPLE__
    if (keycode == 53)
#else
    if (keycode == 65307)
#endif
    {
        cleanup_scene(scene);
        exit(0);
    }
    return (keycode);
}

static int clean_and_exit(void *param)
{
    cleanup_scene((t_scene *)param);
    exit(0);
    return (0);
}

static void init_mlx_instance(t_graph *mlx)
{
    mlx->mlx = mlx_init();
    if (!mlx->mlx)
    {
        printf("Error: Mlx init\n");
        exit(1);
    }
}

static void init_mlx_window(t_graph *mlx)
{
    mlx->mlx_win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "MiniRT");
    if (!mlx->mlx_win)
    {
        destroy_mlx(mlx);
        printf("Error: Mlx win\n");
        exit(1);
    }
}

static void init_mlx_image(t_graph *mlx)
{
    mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
    if (!mlx->img)
    {
        destroy_mlx(mlx);
        printf("Error: Mlx img\n");
        exit(1);
    }
    mlx->address = mlx_get_data_addr(mlx->img, &mlx->bpp,
        &mlx->line_length, &mlx->endian);
    if (!mlx->address)
    {
        destroy_mlx(mlx);
        printf("Error addr\n");
        exit(1);
    }
}

void init_mlx(t_scene *scene)
{
    t_graph *mlx;

    mlx = &scene->mlx;
    init_mlx_instance(mlx);
    init_mlx_window(mlx);
    init_mlx_image(mlx);
    mlx_key_hook(mlx->mlx_win, mlx_signals, scene);
    mlx_hook(mlx->mlx_win, 17, 0, clean_and_exit, scene);
}

void start_mlx_loop(t_scene *scene)
{
    mlx_hook(scene->mlx.mlx_win, 2, 1L<<0, mlx_signals, scene);
    mlx_loop(scene->mlx.mlx);
}
