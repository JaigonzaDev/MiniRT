#include "graph.h"
#include "../render/render.h"
#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>

#define ESC_KEY 53

int clean_and_exit(void *param)
{
    (void)param;
    exit(0);
    return (0);
}

int mlx_signals(int keycode, void *param)
{
    (void)param;
    if (keycode == ESC_KEY)
        clean_and_exit(param);
    // else if (keycode == 13) // W
    //     //camera
    return (0);
}

void init_mlx(t_graph *mlx)
{
    mlx->mlx = mlx_init();
    if (!mlx->mlx)
    {
        printf("Error: Mlx init\n");
        exit(1);
    }
    mlx->mlx_win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "MiniRT");
    if (!mlx->mlx_win)
    {
        printf("Error: Mlx win\n");
        exit(1);
    }
    mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
    if (!mlx->img)
    {
        printf("Error: Mlx img\n");
        exit(1);
    }
    mlx->address = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_len, &mlx->endian);
    if (!mlx->address)
    {
        printf("Error: addr\n");
        exit(1);
    }
    mlx_key_hook(mlx->mlx_win, mlx_signals, mlx);
    mlx_hook(mlx->mlx_win, 17, 0, clean_and_exit, mlx); // Window close button (cross)
}