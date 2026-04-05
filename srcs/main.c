/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 10:00:35 by jaigonza          #+#    #+#             */
/*   Updated: 2026/04/05 10:04:38 by jaigonza         ###   ########.fr       */
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
	mlx_loop(scene.mlx.mlx);
	cleanup_scene(&scene);
	return (0);
}
