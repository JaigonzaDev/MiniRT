#include "main.h"

void parse_sphere(char **line, t_sphere *scene)
{
    if (scene->id != NULL)
        printf("Error: Already Assigned\n");
    scene->id = "sp";
    (*line) += 2;
    skip_space(line);
    insert_data_vector(line, &scene->center);
    skip_space(line);
    scene->diameter = get_double(line);
    skip_space(line);
    insert_data_vector(line, &scene->rgb);
}

void parse_plane(char **line, t_plane *scene)
{
    if (scene->id != NULL)
        printf("Error: Already Assigned\n");
    scene->id = "pl";
    (*line) += 2;
    skip_space(line);
    insert_data_vector(line, &scene->point);
    skip_space(line);
    insert_data_vector(line, &scene->normalized);
    skip_space(line);
    insert_data_vector(line, &scene->rgb);
}

void parse_cylinder(char **line, t_cylinder *scene)
{
    if (scene->id != NULL)
        printf("Error: Already Assigned\n");
    scene->id = "cy";
    (*line) += 2;
    skip_space(line);
    insert_data_vector(line, &scene->center);
    skip_space(line);
    insert_data_vector(line, &scene->normalized);
    skip_space(line);
    scene->diameter = get_double(line);
    skip_space(line);
    scene->height = get_double(line);
    skip_space(line);
    insert_data_vector(line, &scene->rgb);
}

/*
** Inicializa la cámara
** Esta función puede usarse para validar o configurar la cámara después del parsing
** Por ahora solo es un placeholder que verifica que la cámara existe
*/
void init_camera(t_camera camera)
{
    if (camera.id == NULL)
    {
        printf("Error: Camera not initialized\n");
        exit(1);
    }
    // Aquí se podría agregar más validación de la cámara si es necesario
    (void)camera;
}
