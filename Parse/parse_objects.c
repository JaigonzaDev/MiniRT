#include "main.h"

void parse_sphere(char **line, t_sphere **list)
{
    t_sphere *new_node = malloc(sizeof(t_sphere));
    if (!new_node)
        exit(1);
    new_node->next = NULL;
    new_node->id = "sp";
    (*line) += 2;
    skip_space(line);
    insert_data_vector(line, &new_node->center);
    skip_space(line);
    new_node->diameter = get_double(line);
    skip_space(line);
    insert_data_vector(line, &new_node->rgb);

    if (*list == NULL)
        *list = new_node;
    else
    {
        t_sphere *tmp = *list;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_node;
    }
}

void parse_plane(char **line, t_plane **list)
{
    t_plane *new_node = malloc(sizeof(t_plane));
    if (!new_node)
        exit(1);
    new_node->next = NULL;
    new_node->id = "pl";
    (*line) += 2;
    skip_space(line);
    insert_data_vector(line, &new_node->point);
    skip_space(line);
    insert_data_vector(line, &new_node->normalized);
    skip_space(line);
    insert_data_vector(line, &new_node->rgb);

    if (*list == NULL)
        *list = new_node;
    else
    {
        t_plane *tmp = *list;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_node;
    }
}

void parse_cylinder(char **line, t_cylinder **list)
{
    t_cylinder *new_node = malloc(sizeof(t_cylinder));
    if (!new_node)
        exit(1);
    new_node->next = NULL;
    new_node->id = "cy";
    (*line) += 2;
    skip_space(line);
    insert_data_vector(line, &new_node->center);
    skip_space(line);
    insert_data_vector(line, &new_node->normalized);
    skip_space(line);
    new_node->diameter = get_double(line);
    skip_space(line);
    new_node->height = get_double(line);
    skip_space(line);
    insert_data_vector(line, &new_node->rgb);

    if (*list == NULL)
        *list = new_node;
    else
    {
        t_cylinder *tmp = *list;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_node;
    }
}