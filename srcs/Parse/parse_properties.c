#include "main.h"

static bool is_comment_or_empty(char *ptr)
{
    return (*ptr == '\0' || *ptr == '\n' || *ptr == '#');
}

static bool handle_property(char *ptr, t_scene *scene)
{
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
        return (false);
    return (true);
}

void parse_properties(char *line, t_scene *scene)
{
    char *ptr;

    ptr = line;
    skip_space(&ptr);
    if (is_comment_or_empty(ptr))
        return;
    if (!handle_property(ptr, scene))
    {
        printf("Error\nProperties not well defined\n");
        exit(1);
    }
}

static void validate_extension(char **av)
{
    int	len;
    bool	valid_ext;

    len = strlen(av[1]);
    valid_ext = false;
    if (len >= 3 && strncmp(av[1] + len - 3, ".rt", 3) == 0)
        valid_ext = true;
    else if (len >= 2 && strncmp(av[1] + len - 2, ".r", 2) == 0)
        valid_ext = true;
    if (!valid_ext)
    {
        printf("Error\nInvalid file extension\n");
        exit(1);
    }
}

static int open_scene_file(char **av)
{
    int fd;

    fd = open(av[1], O_RDONLY);
    if (fd < 0)
    {
        printf("Error\nOpen file failed\n");
        exit(1);
    }
    return (fd);
}

void parse(char **av, t_scene *scene)
{
    int	 fd;
    char *line;

    if (av == NULL || *av == NULL || av[1] == NULL)
        exit(1);
    validate_extension(av);
    fd = open_scene_file(av);
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