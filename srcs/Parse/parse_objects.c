#include "main.h"

static t_sphere	*create_sphere_node(char **line)
{
	t_sphere	*new_node;

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
	validate_line_end(line);
	return (new_node);
}

static void	append_sphere(t_sphere **list, t_sphere *new_node)
{
	t_sphere	*tmp;

	if (*list == NULL)
	{
		*list = new_node;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

void	parse_sphere(char **line, t_sphere **list)
{
	append_sphere(list, create_sphere_node(line));
}
