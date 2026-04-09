/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 12:12:43 by rlobun            #+#    #+#             */
/*   Updated: 2026/04/08 19:38:58 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	validate_cylinder(t_cylinder *cy)
{
	if (vector_length(cy->normalized) <= EPSILON)
	{
		printf("Error\nCylinder axis vector cannot be zero\n");
		exit(1);
	}
	cy->normalized = vector_normal(cy->normalized);
	if (cy->diameter <= EPSILON)
	{
		printf("Error\nCylinder diameter must be > 0\n");
		exit(1);
	}
	if (cy->height <= EPSILON)
	{
		printf("Error\nCylinder height must be > 0\n");
		exit(1);
	}
}

static t_cylinder	*create_cylinder_node(char **line)
{
	t_cylinder	*new_node;

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
	validate_line_end(line);
	validate_cylinder(new_node);
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

void	parse_cylinder(char **line, t_cylinder **list)
{
	append_cylinder(list, create_cylinder_node(line));
}
