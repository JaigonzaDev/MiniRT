
void parse_sphere(char *line, t_sphere *scene)
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

void parse_plane(char *line, t_plane *scene)
{
    if (scene != NULL)
        printf("Error: Already Assigned");
    scene->id = 'pl';
    skip_spaces(*line);
    scene->point = ft_atoi();
    skip_spaces(*line);
    scene->normalized = ft_atoi();
    skip_spaces(*line);
    scene->rgb = ft_atoi();
}

void parse_cylinder(char *line, t_cylinder *scene)
{
    if (scene != NULL)
        printf("Error: Already Assigned");
    scene->id = 'cy';
    skip_spaces(*line);
    scene->center = ft_atoi(); // Vector
    skip_spaces(*line);
    scene->normalized = ft_atoi(); // Vector
    skip_spaces(*line);
    scene->diameter = ft_atoi();
    skip_spaces(*line);
    scene->height = ft_atoi();
    skip_spaces(*line);
    scene->rgb = ft_atoi();
}