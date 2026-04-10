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

static t_plane	*create_plane_node(char **line)
{
	t_plane	*new_node;

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
	if (vector_length(new_node->normalized) <= EPSILON)
	{
		printf("Error\nPlane normal vector cannot be zero\n");
		exit(1);
	}
	new_node->normalized = vector_normal(new_node->normalized);
	skip_space(line);
	insert_data_vector(line, &new_node->rgb);
	validate_line_end(line);
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

void	parse_plane(char **line, t_plane **list)
{
	append_plane(list, create_plane_node(line));
}
