#include "graph.h"
#include "main.h"
#include "render.h"
#include <mlx.h>
#include <stdlib.h>

int	mlx_close(void *param)
{
	cleanup_scene((t_scene *)param);
	exit(0);
	return (0);
}

void	start_mlx_loop(t_scene *scene)
{
	mlx_hook(scene->mlx.mlx_win, 2, 1L << 0, mlx_signals, scene);
	mlx_loop(scene->mlx.mlx);
}

#ifndef __APPLE__

static void	free_linux_mlx(t_graph *mlx)
{
	if (mlx->mlx)
	{
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
		mlx->mlx = NULL;
	}
}

#else

static void	free_linux_mlx(t_graph *mlx)
{
	(void)mlx;
}

#endif

void	destroy_mlx(t_graph *mlx)
{
	if (!mlx)
		return ;
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
	free_linux_mlx(mlx);
}
