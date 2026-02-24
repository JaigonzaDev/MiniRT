#include "main.h"
#include <stdio.h>
#include <string.h>

int main (int ac, char **av)
{
    if (ac != 2)
    {
        printf("Error: Num arguments");
        return (1);
    }
    else
    {
        t_scene scene;

        memset(&scene, 0, sizeof(t_scene));

        parse(av, &scene);
        init_mlx(scene.mlx);
        init_camera(scene.camera);
        render(scene);
        mlx_loop();
        return (0);
    }
}