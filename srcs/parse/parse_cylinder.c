/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 12:12:43 by rlobun            #+#    #+#             */
/*   Updated: 2026/04/08 19:38:58 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static bool	validate_cylinder(t_cylinder *cy)
{
	if (vector_length(cy->normalized) <= EPSILON)
	{
		printf("Error\nCylinder axis vector cannot be zero\n");
		return (false);
	}
	cy->normalized = vector_normal(cy->normalized);
	if (cy->diameter <= EPSILON)
	{
		printf("Error\nCylinder diameter must be > 0\n");
		return (false);
	}
	if (cy->height <= EPSILON)
	{
		printf("Error\nCylinder height must be > 0\n");
		return (false);
	}
	return (true);
}

static bool	init_cylinder_node(t_cylinder *new_node, char **line)
{
	(*line) += 2;
	skip_space(line);
	if (!insert_data_vector(line, &new_node->center))
		return (false);
	skip_space(line);
	if (!insert_data_vector(line, &new_node->normalized))
		return (false);
	skip_space(line);
	if (!get_double(line, &new_node->diameter))
		return (false);
	skip_space(line);
	if (!get_double(line, &new_node->height))
		return (false);
	skip_space(line);
	if (!insert_data_vector(line, &new_node->rgb))
		return (false);
	if (!validate_line_end(line))
		return (false);
	if (!validate_cylinder(new_node))
		return (false);
	return (true);
}

static t_cylinder	*create_cylinder_node(char **line)
{
	t_cylinder	*new_node;

	new_node = malloc(sizeof(t_cylinder));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->id = "cy";
	if (!init_cylinder_node(new_node, line))
		return (free(new_node), NULL);
	return (new_node);
}

static void	append_cylinder(t_cylinder **list, t_cylinder *new_node)
{
	t_cylinder	*tmp;

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

bool	parse_cylinder(char **line, t_cylinder **list)
{
	t_cylinder	*node;

	node = create_cylinder_node(line);
	if (!node)
		return (false);
	append_cylinder(list, node);
	return (true);
}
