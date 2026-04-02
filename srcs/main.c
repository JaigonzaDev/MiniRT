/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 12:00:00 by jaigonza          #+#    #+#             */
/*   Updated: 2026/04/02 12:00:00 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	t_scene	scene;

	if (ac != 2)
	{
		printf("Error: Num arguments\n");
		return (1);
	}
	memset(&scene, 0, sizeof(t_scene));
	parse(av, &scene);
	init_mlx(&scene);
	ft_init_viewport(&scene);
	ft_render(&scene);
	if (getenv("ONE_SHOT"))
	{
		cleanup_scene(&scene);
		return (0);
	}
	mlx_loop(scene.mlx.mlx);
	cleanup_scene(&scene);
	return (0);
}
