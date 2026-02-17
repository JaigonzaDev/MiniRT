#include "main.h"

int main (int ac, char **av)
{
    if (ac != 2)
    {
        ft_printf("Error: Num arguments");
        return (1);
    }
    else
    {
        t_scene scene;
        parse_properties(av, scene);
        init_mlx(scene.mlx);
        init_viewport(scene.camera);
        render(scene);
        //mlx_loop();
        return (0);
    }
}