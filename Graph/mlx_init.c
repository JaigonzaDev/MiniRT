#include "graph.h"
#include "../main.h"
#include "../render/render.h"
#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef __APPLE__
# define KEY_TAB 48
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_Q 12
# define KEY_E 14
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
#else
# define KEY_TAB 65289
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_Q 113
# define KEY_E 101
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
#endif

static t_vector vector_rotate_y(t_vector vec, double angle)
{
    t_vector res;
    res.x = vec.x * cos(angle) + vec.z * sin(angle);
    res.y = vec.y;
    res.z = -vec.x * sin(angle) + vec.z * cos(angle);
    return res;
}

static t_vector vector_rotate_x(t_vector vec, double angle)
{
    t_vector res;
    res.x = vec.x;
    res.y = vec.y * cos(angle) - vec.z * sin(angle);
    res.z = vec.y * sin(angle) + vec.z * cos(angle);
    return res;
}

int mlx_signals(int keycode, void *param)
{
    t_scene *scene;
    int moved = 0;

    scene = (t_scene *)param;
    if (keycode == KEY_ESC)
    {
        cleanup_scene(scene);
        exit(0);
    }
    else if (keycode == KEY_TAB)
    {
        scene->active_type = (scene->active_type + 1) % 5;
        if (scene->active_type == 0) scene->active_obj = &scene->camera;
        else if (scene->active_type == 1) scene->active_obj = &scene->light;
        else if (scene->active_type == 2) scene->active_obj = scene->sphere;
        else if (scene->active_type == 3) scene->active_obj = scene->plane;
        else if (scene->active_type == 4) scene->active_obj = scene->cylinder;
        printf("Active object changed to %d\n", scene->active_type);
    }
    else if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_A || keycode == KEY_D || keycode == KEY_Q || keycode == KEY_E || keycode == KEY_UP || keycode == KEY_DOWN || keycode == KEY_LEFT || keycode == KEY_RIGHT)
    {
        t_vector *pos = NULL;
        t_vector *dir = NULL;
        if (scene->active_type == 0) { pos = &scene->camera.viewpoint; dir = &scene->camera.orientation; }
        else if (scene->active_type == 1) { pos = &scene->light.light_point; }
        else if (scene->active_type == 2 && scene->active_obj) { pos = &((t_sphere*)scene->active_obj)->center; }
        else if (scene->active_type == 3 && scene->active_obj) { pos = &((t_plane*)scene->active_obj)->point; dir = &((t_plane*)scene->active_obj)->normalized; }
        else if (scene->active_type == 4 && scene->active_obj) { pos = &((t_cylinder*)scene->active_obj)->center; dir = &((t_cylinder*)scene->active_obj)->normalized; }
        
        if (pos)
        {
            if (keycode == KEY_W) { pos->z += 1.0; moved = 1; }
            else if (keycode == KEY_S) { pos->z -= 1.0; moved = 1; }
            else if (keycode == KEY_A) { pos->x -= 1.0; moved = 1; }
            else if (keycode == KEY_D) { pos->x += 1.0; moved = 1; }
            else if (keycode == KEY_Q) { pos->y += 1.0; moved = 1; }
            else if (keycode == KEY_E) { pos->y -= 1.0; moved = 1; }
        }
        if (dir)
        {
            if (keycode == KEY_LEFT) { *dir = vector_rotate_y(*dir, -0.1); moved = 1; }
            else if (keycode == KEY_RIGHT) { *dir = vector_rotate_y(*dir, 0.1); moved = 1; }
            else if (keycode == KEY_UP) { *dir = vector_rotate_x(*dir, -0.1); moved = 1; }
            else if (keycode == KEY_DOWN) { *dir = vector_rotate_x(*dir, 0.1); moved = 1; }
            *dir = vector_normal(*dir);
        }
    }

    if (moved)
    {
        if (scene->active_type == 0)
            ft_init_viewport(scene);
        ft_render(scene);
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
