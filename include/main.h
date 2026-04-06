/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 12:13:47 by jaigonza          #+#    #+#             */
/*   Updated: 2026/04/06 19:01:03 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libft.h"
# include "render.h"
# include "graph.h"
# include "vector.h"
# include "objects.h"
# include "properties.h"

typedef struct s_scene
{
	t_graph		mlx;

	t_camera	camera;
	t_ambient	ambient;
	t_light		light;

	t_cylinder	*cylinder;
	t_sphere	*sphere;
	t_plane		*plane;
}	t_scene;

void	cleanup_scene(t_scene *scene);
void	destroy_mlx(t_graph *mlx);

#endif
