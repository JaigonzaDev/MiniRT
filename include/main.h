/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 12:00:00 by jaigonza          #+#    #+#             */
/*   Updated: 2026/04/02 12:00:00 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MAIN_H
#define MAIN_H

#include "graph.h"
#include "vector.h"
#include "objects.h"
#include "properties.h"

typedef struct s_scene
{
	t_graph mlx;

	t_camera camera;
	t_ambient ambient;
	t_light light;

	t_cylinder *cylinder;
	t_sphere *sphere;
	t_plane *plane;
} t_scene;

#include "render.h"

void    cleanup_scene(t_scene *scene);
void    destroy_mlx(t_graph *mlx);

#endif
