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
        printf("Parsed successfully\n");
        init_mlx(&scene.mlx);
        printf("MLX initialized\n");
        init_camera(scene.camera);
        printf("Camera initialized\n");
        render(scene);
        printf("Rendering complete\n");
        
        // Guardar sin mostrar
        // start_mlx_loop(&scene);
        return (0);
        return (0);
    }
}