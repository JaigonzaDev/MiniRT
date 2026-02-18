void parse_ambient(char *line, t_ambient *scene)
{
    if (scene != NULL)
        printf("Error: Already Assigned");
    scene->id = 'A';
    skip_spaces(*line);
    scene->light_ratio = ft_atoi();
    skip_spaces(*line);
    scene->rgb = ft_atoi();
}

void parse_camera(char *line, t_camera *scene)
{
    if (scene != NULL)
        printf("Error: Already Assigned");
    scene->id = 'C';
    skip_spaces(*line);
    scene->viewpoint = ft_atoi();
    skip_spaces(*line);
    scene->orientation = ft_atoi();
    skip_spaces(*line);
    scene->fov = ft_atoi();
}

void parse_light(char *line, t_light *scene)
{
    if (scene != NULL)
        printf("Error: Already Assigned");
    scene->id = 'L';
    skip_spaces(*line);
    scene->light_point = ft_atoi();
    skip_spaces(*line);
    scene->brightness = ft_atoi();
    skip_spaces(*line);
    scene->rgb = ft_atoi();
}