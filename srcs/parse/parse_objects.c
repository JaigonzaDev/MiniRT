/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 12:12:50 by rlobun            #+#    #+#             */
/*   Updated: 2026/04/08 19:38:58 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (new_node->diameter <= EPSILON)
	{
		printf("Error\nSphere diameter must be > 0\n");
		exit(1);
	}
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
