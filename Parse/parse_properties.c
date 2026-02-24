#include "main.h"

void parse_properties(char *line, t_scene *scene)
{
    char *ptr = line;
    skip_space(&ptr);
    if (*ptr == '\0' || *ptr == '\n')
        return;
    if (strncmp(ptr, "A", 1) == 0 && (ptr[1] == ' ' || ptr[1] == '\t'))
        parse_ambient(&ptr, &scene->ambient);
    else if (strncmp(ptr, "C", 1) == 0 && (ptr[1] == ' ' || ptr[1] == '\t'))
        parse_camera(&ptr, &scene->camera);
    else if (strncmp(ptr, "L", 1) == 0 && (ptr[1] == ' ' || ptr[1] == '\t'))
        parse_light(&ptr, &scene->light);
    else if (strncmp(ptr, "sp", 2) == 0 && (ptr[2] == ' ' || ptr[2] == '\t'))
        parse_sphere(&ptr, &scene->sphere);
    else if (strncmp(ptr, "pl", 2) == 0 && (ptr[2] == ' ' || ptr[2] == '\t'))
        parse_plane(&ptr, &scene->plane);
    else if (strncmp(ptr, "cy", 2) == 0 && (ptr[2] == ' ' || ptr[2] == '\t'))
        parse_cylinder(&ptr, &scene->cylinder);
    else
    {
        printf("Error\nProperties not well defined\n");
        exit(1);
    }
}

void parse(char **av, t_scene *scene) 
{
    if (av == NULL || *av == NULL || av[1] == NULL)
        exit(1);
    
    int len = strlen(av[1]);
    if (len < 3 || strncmp(av[1] + len - 3, ".rt", 3) != 0)
    {
        printf("Error\nInvalid file extension\n");
        exit(1);
    }

    int fd = open(av[1], O_RDONLY);
    if (fd < 0)
    {
        printf("Error\nOpen file failed\n");
        exit(1);
    }

    char *line;
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        parse_properties(line, scene);
        free(line);
    }
    close(fd);
}