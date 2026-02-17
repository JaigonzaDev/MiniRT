#include "graph.h"
int mlx_signals(int keycode, )
{
    if (keycode == ESC)
        clean_and_exit();
    else if (keycode == W)
        //camera
    else if (keycode == A)
        //camera
    else if (keycode == S)
        //camera
    else if (keycode == D)
        //camera
    else if (keycode == C)
        //camera
    else if (keycode == V)
        //camera
    render();
    return (keycode);
}
void init_mlx(t_graph *mlx)
{
    mlx->mlx = mlx_init();
    if (!mlx->mlx)
        printf("Error: Mlx init");
    mlx->mlx_win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "MiniRT");
    if (!mlx->mlx_win)
        printf("Error: Mlx win");
    mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT, "MiniRT");
    if (!mlx->img)
        printf("Error: Mlx img");
    mlx->address = mlx_get_data_addr("???");
    if (!mlx->address)
        printf("Error addr");
    mlx_hook();
}