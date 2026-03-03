#include "main.h"
#include <stdio.h>
#include <string.h>
#include <mlx.h>



int main (int ac, char **av)
{
    if (ac != 2)
    {
        printf("Error: Num arguments\n");
        return (1);
    }
    else
    {
        t_scene scene;

        memset(&scene, 0, sizeof(t_scene));

        parse(av, &scene);
        init_mlx(&scene.mlx);
        ft_init_viewport(&scene);
        ft_render(&scene);
        mlx_loop(scene.mlx.mlx);
        return (0);
    }
}