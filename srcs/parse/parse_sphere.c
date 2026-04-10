/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 12:12:50 by rlobun            #+#    #+#             */
/*   Updated: 2026/04/08 19:38:58 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static bool	init_sphere_node(t_sphere *new_node, char **line)
{
	(*line) += 2;
	skip_space(line);
	if (!insert_data_vector(line, &new_node->center))
		return (false);
	skip_space(line);
	if (!get_double(line, &new_node->diameter))
		return (false);
	if (new_node->diameter <= EPSILON)
		return (printf("Error\nSphere diameter must be > 0\n"), false);
	skip_space(line);
	if (!insert_data_vector(line, &new_node->rgb))
		return (false);
	if (!validate_rgb(new_node->rgb))
		return (printf("Error\nSphere RGB out of range [0-255]\n"), false);
	if (!validate_line_end(line))
		return (false);
	return (true);
}

static t_sphere	*create_sphere_node(char **line)
{
	t_sphere	*new_node;

	new_node = malloc(sizeof(t_sphere));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->id = "sp";
	if (!init_sphere_node(new_node, line))
		return (free(new_node), NULL);
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

bool	parse_sphere(char **line, t_sphere **list)
{
	t_sphere	*node;

	node = create_sphere_node(line);
	if (!node)
		return (false);
	append_sphere(list, node);
	return (true);
}
