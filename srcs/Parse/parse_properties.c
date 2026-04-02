/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_properties.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 12:00:00 by jaigonza          #+#    #+#             */
/*   Updated: 2026/04/02 12:00:00 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"

static bool	is_comment_or_empty(char *ptr)
{
	return (*ptr == '\0' || *ptr == '\n' || *ptr == '#');
}

static bool	handle_property(char *ptr, t_scene *scene)
{
	if (strncmp(ptr, "A", 1) == 0 && (ptr[1] == ' ' || ptr[1] == '\t'))
		parse_ambient(&ptr, &scene->ambient);
	else if (strncmp(ptr, "C", 1) == 0 && (ptr[1] == ' ' || ptr[1] == '\t'))
		parse_camera(&ptr, &scene->camera);
	else if (strncmp(ptr, "L", 1) == 0 && (ptr[1] == ' ' || ptr[1] == '\t'))
		parse_light(&ptr, &scene->light);
	else if (strncmp(ptr, "sp", 2) == 0 && (ptr[2] == ' ' || ptr[2] == '\t'))
		parse_sphere(&ptr, &scene->sphere);
	else if (strncmp(ptr, "pl", 2) == 0 && (ptr[2] == ' ' || ptr[2] == '\t'))
		parse_plane(&ptr, &scene->plane);
	else if (strncmp(ptr, "cy", 2) == 0 && (ptr[2] == ' ' || ptr[2] == '\t'))
		parse_cylinder(&ptr, &scene->cylinder);
	else
		return (false);
	return (true);
}

void	parse_properties(char *line, t_scene *scene)
{
	char	*ptr;

	ptr = line;
	skip_space(&ptr);
	if (is_comment_or_empty(ptr))
		return ;
	if (!handle_property(ptr, scene))
	{
		printf("Error\nProperties not well defined\n");
		exit(1);
	}
}
