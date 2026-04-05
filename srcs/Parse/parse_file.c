/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlobun <rlobun@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 17:01:01 by rlobun            #+#    #+#             */
/*   Updated: 2026/04/05 17:01:07 by rlobun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	validate_extension(char **av)
{
	int		len;
	bool	valid_ext;

	len = strlen(av[1]);
	valid_ext = false;
	if (len >= 3 && strncmp(av[1] + len - 3, ".rt", 3) == 0)
		valid_ext = true;
	else if (len >= 2 && strncmp(av[1] + len - 2, ".r", 2) == 0)
		valid_ext = true;
	if (!valid_ext)
	{
		printf("Error\nInvalid file extension\n");
		exit(1);
	}
}

static int	open_scene_file(char **av)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nOpen file failed\n");
		exit(1);
	}
	return (fd);
}

void	parse(char **av, t_scene *scene)
{
	int		fd;
	char	*line;

	if (av == NULL || *av == NULL || av[1] == NULL)
		exit(1);
	validate_extension(av);
	fd = open_scene_file(av);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		parse_properties(line, scene);
		free(line);
	}
	close(fd);
}
