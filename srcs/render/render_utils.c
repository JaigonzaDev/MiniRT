/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 12:00:00 by jaigonza          #+#    #+#             */
/*   Updated: 2026/04/02 12:00:00 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "render.h"
#include "main.h"

static void	render_pixel(t_scene *scene, int x, int y)
{
	t_vector	factors;
	t_ray		ray;
	t_hit		pixel;

	pixel.color = BLACK;
	pixel.shape = NULL;
	pixel.t = INFINITY;
	factors = ft_canvas_to_viewport(x, y);
	ray = ft_cast_ray(scene, factors);
	if (ft_obj_hit(scene, &ray, &pixel))
		ft_illuminate(scene, &pixel);
	ft_put_pixel(scene, pixel.color, x, y);
}

int	ft_render(t_scene *scene)
{
	t_vector	coords;

	coords.y = -1;
	while (++coords.y < HEIGHT)
	{
		coords.x = -1;
		while (++coords.x < WIDTH)
			render_pixel(scene, (int)coords.x, (int)coords.y);
	}
	mlx_put_image_to_window(scene->mlx.mlx, scene->mlx.mlx_win, \
		scene->mlx.img, 0, 0);
	ft_save_image(scene, "output_new.ppm");
	return (0);
}
