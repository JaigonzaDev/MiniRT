/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_properties.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 12:12:35 by rlobun            #+#    #+#             */
/*   Updated: 2026/04/06 18:56:45 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"

static bool	is_comment_or_empty(char *ptr)
{
	return (*ptr == '\0' || *ptr == '\n' || *ptr == '#');
}

static bool	handle_property(char *ptr, t_scene *scene)
{
	if (ft_strncmp(ptr, "A", 1) == 0 && (ptr[1] == ' ' || ptr[1] == '\t'))
		return (parse_ambient(&ptr, &scene->ambient));
	else if (ft_strncmp(ptr, "C", 1) == 0 && (ptr[1] == ' ' || ptr[1] == '\t'))
		return (parse_camera(&ptr, &scene->camera));
	else if (ft_strncmp(ptr, "L", 1) == 0 && (ptr[1] == ' ' || ptr[1] == '\t'))
		return (parse_light(&ptr, &scene->light));
	else if (ft_strncmp(ptr, "sp", 2) == 0 && (ptr[2] == ' ' || ptr[2] == '\t'))
		return (parse_sphere(&ptr, &scene->sphere));
	else if (ft_strncmp(ptr, "pl", 2) == 0 && (ptr[2] == ' ' || ptr[2] == '\t'))
		return (parse_plane(&ptr, &scene->plane));
	else if (ft_strncmp(ptr, "cy", 2) == 0 && (ptr[2] == ' ' || ptr[2] == '\t'))
		return (parse_cylinder(&ptr, &scene->cylinder));
	return (false);
}

bool	parse_properties(char *line, t_scene *scene)
{
	char	*ptr;

	ptr = line;
	skip_space(&ptr);
	if (is_comment_or_empty(ptr))
		return (true);
	if (!handle_property(ptr, scene))
	{
		printf("Error\nProperties not well defined\n");
		return (false);
	}
	return (true);
}
