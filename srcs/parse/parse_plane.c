/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 17:02:31 by rlobun            #+#    #+#             */
/*   Updated: 2026/04/08 19:38:58 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static bool	init_plane_node(t_plane *new_node, char **line)
{
	(*line) += 2;
	skip_space(line);
	if (!insert_data_vector(line, &new_node->point))
		return (false);
	skip_space(line);
	if (!insert_data_vector(line, &new_node->normalized))
		return (false);
	if (!validate_normalized_vector(new_node->normalized))
		return (printf("Error\nPlane normal out of bounds [-1, 1]\n"), false);
	if (vector_length(new_node->normalized) <= EPSILON)
		return (printf("Error\nPlane normal vector cannot be zero\n"), false);
	new_node->normalized = vector_normal(new_node->normalized);
	skip_space(line);
	if (!insert_data_vector(line, &new_node->rgb))
		return (false);
	if (!validate_rgb(new_node->rgb))
		return (printf("Error\nPlane RGB out of range [0-255]\n"), false);
	if (!validate_line_end(line))
		return (false);
	return (true);
}

static t_plane	*create_plane_node(char **line)
{
	t_plane	*new_node;

	new_node = malloc(sizeof(t_plane));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->id = "pl";
	if (!init_plane_node(new_node, line))
		return (free(new_node), NULL);
	return (new_node);
}

static void	append_plane(t_plane **list, t_plane *new_node)
{
	t_plane	*tmp;

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

bool	parse_plane(char **line, t_plane **list)
{
	t_plane	*node;

	node = create_plane_node(line);
	if (!node)
		return (false);
	append_plane(list, node);
	return (true);
}
