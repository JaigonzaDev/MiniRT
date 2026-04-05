/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 10:00:45 by jaigonza          #+#    #+#             */
/*   Updated: 2026/04/05 10:04:36 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <mlx.h>
#include <stdlib.h>

static void	free_spheres(t_sphere **list)
{
	t_sphere	*cur;
	t_sphere	*next;

	if (list)
		cur = *list;
	else
		cur = NULL;
	while (cur)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	if (list)
		*list = NULL;
}

static void	free_planes(t_plane **list)
{
	t_plane	*cur;
	t_plane	*next;

	if (list)
		cur = *list;
	else
		cur = NULL;
	while (cur)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	if (list)
		*list = NULL;
}

static void	free_cylinders(t_cylinder **list)
{
	t_cylinder	*cur;
	t_cylinder	*next;

	if (list)
		cur = *list;
	else
		cur = NULL;
	while (cur)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	if (list)
		*list = NULL;
}

void	cleanup_scene(t_scene *scene)
{
	if (!scene)
		return ;
	free_spheres(&scene->sphere);
	free_planes(&scene->plane);
	free_cylinders(&scene->cylinder);
	destroy_mlx(&scene->mlx);
}
