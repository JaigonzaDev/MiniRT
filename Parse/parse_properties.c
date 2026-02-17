#include "main.h"

void parse_ambient(char *line, t_ambient *scene)
{

}

void parse_camera(char *line, t_camera *scene)
{

}

void parse_light(char *line, t_light *scene)
{

}

void parse_sphere(char *line, t_sphere *scene)
{

}

void parse_plane(char *line, t_plane *scene)
{

}

void parse_cylinder(char *line, t_cylinder *scene)
{

}

void parse_proporties(char *line, t_scene *scene)
{
    while (*line != NULL) 
    {
        if (*line == 'A')
            parse_ambient(scene->ambient);
        else if (*line == 'C')
            parse_camera(scene->camera);
        else if (*line == 'L')
            parse_light(scene->light);
        else if (ft_strncmp(sp))
            parse_sphere(scene->sphere);
        else if (ft_strncmp(pl))
            parse_plane(scene->plane);
        else if (ft_strncmp(cy))
            parse_cylinder(scene->cylinder);
        else
            ft_printf("Error: Properties not well defined\n");
    }
}

void parse(char **av, t_scene *scene) 
{

    if (av == NULL || *av == NULL)
        return (NULL);
    int fd;
    char *line;

    fd = open(av[1], O_RDONLY);
    if (fd < 0)
        printf("Error: Open file");
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        if (!ft_strchr("\n", line[0]))
            parse_properties(line, scene);
        else
            free(line);
    }
}