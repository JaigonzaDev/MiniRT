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
	mlx_hook(scene->mlx.mlx_win, 2, 1L<<0, mlx_signals, scene);
	mlx_loop(scene->mlx.mlx);
}
