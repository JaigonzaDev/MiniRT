
void parse_sphere(char *line, t_sphere *scene)
{
    if (scene != NULL)
        printf("Error: Already Assigned");
    scene->id = "sp";
    skip_spaces(*line);
    insert_data_vector(line, scene->center);
    skip_spaces(*line);
    scene->diameter = ft_atoi();
    skip_spaces(*line);
    scene->height = ft_atoi();
    insert_data_vector(line, scene->rgb);
}

void parse_plane(char *line, t_plane *scene)
{
    if (scene != NULL)
        printf("Error: Already Assigned");
    scene->id = 'pl';
    insert_data_vector(line, scene->point);
    insert_data_vector(line, scene->normalized);
    insert_data_vector(line, scene->rgb);
}

void parse_cylinder(char *line, t_cylinder *scene)
{
    if (scene != NULL)
        printf("Error: Already Assigned");
    scene->id = 'cy';
    skip_spaces(*line);
    insert_data_vector(line, scene->center);
    insert_data_vector(line, scene->normalized);
    scene->diameter = ft_atoi();
    skip_spaces(*line);
    scene->height = ft_atoi();
    insert_data_vector(line, scene->rgb);
}