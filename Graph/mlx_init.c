#include "graph.h"
#include "../main.h"
#include <mlx.h>

int mlx_signals(int keycode, void *param)
{
    (void)param;
    if (keycode == 65307) // ESC key
        exit(0);
    return (keycode);
}

void init_mlx(t_graph *mlx)
{
    mlx->mlx = mlx_init();
    if (!mlx->mlx)
    {
        printf("Error: Mlx init\n");
        exit(1);
    }
    mlx->mlx_win = mlx_new_window(mlx->mlx, 1920, 1080, "MiniRT");
    if (!mlx->mlx_win)
    {
        printf("Error: Mlx win\n");
        exit(1);
    }
    mlx->img = mlx_new_image(mlx->mlx, 1920, 1080);
    if (!mlx->img)
    {
        printf("Error: Mlx img\n");
        exit(1);
    }
    mlx->address = mlx_get_data_addr(mlx->img, &mlx->bpp, 
        &mlx->line_length, &mlx->endian);
    if (!mlx->address)
    {
        printf("Error addr\n");
        exit(1);
    }
}

void start_mlx_loop(t_scene *scene)
{
    mlx_hook(scene->mlx.mlx_win, 2, 1L<<0, mlx_signals, scene);
    mlx_loop(scene->mlx.mlx);
}