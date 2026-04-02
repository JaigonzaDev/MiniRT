#include "main.h"

static t_sphere *create_sphere_node(char **line)
{
    t_sphere *new_node;

    new_node = malloc(sizeof(t_sphere));
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
    return (new_node);
}

static void append_sphere(t_sphere **list, t_sphere *new_node)
{
    t_sphere *tmp;

    if (*list == NULL)
    {
        *list = new_node;
        return;
    }
    tmp = *list;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
}

static t_plane *create_plane_node(char **line)
{
    t_plane *new_node;

    new_node = malloc(sizeof(t_plane));
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
    return (new_node);
}

static void append_plane(t_plane **list, t_plane *new_node)
{
    t_plane *tmp;

    if (*list == NULL)
    {
        *list = new_node;
        return;
    }
    tmp = *list;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
}

static t_cylinder *create_cylinder_node(char **line)
{
    t_cylinder *new_node;

    new_node = malloc(sizeof(t_cylinder));
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
    return (new_node);
}

static void append_cylinder(t_cylinder **list, t_cylinder *new_node)
{
    t_cylinder *tmp;

    if (*list == NULL)
    {
        *list = new_node;
        return;
    }
    tmp = *list;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
}

void parse_sphere(char **line, t_sphere **list)
{
    append_sphere(list, create_sphere_node(line));
}

void parse_plane(char **line, t_plane **list)
{
    append_plane(list, create_plane_node(line));
}

void parse_cylinder(char **line, t_cylinder **list)
{
    append_cylinder(list, create_cylinder_node(line));
}