/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 12:00:00 by jaigonza          #+#    #+#             */
/*   Updated: 2026/04/02 12:00:00 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "render.h"
#include "main.h"

void	ft_init_viewport(t_scene *scene)
{
	scene->camera.wview = tan(RADIANS(scene->camera.fov / 2.0));
	scene->camera.hview = scene->camera.wview / RATIO;
	scene->camera.right = vector_normal(vector_crossproduct(\
		scene->camera.orientation, UPGUIDE));
	scene->camera.up = vector_normal(vector_crossproduct(\
		scene->camera.orientation, scene->camera.right));
	scene->camera.right = vector_normal(vector_crossproduct(\
		scene->camera.orientation, scene->camera.up));
}

t_vector	ft_canvas_to_viewport(int x, int y)
{
	t_vector	converted;
	double		width;
	double		height;

	width = WIDTH;
	height = HEIGHT;
	converted.x = ((2.0 * x) / width) - 1;
	converted.y = ((2.0 * y) / height) - 1;
	converted.z = 0;
	return (converted);
}

t_ray	ft_cast_ray(t_scene *scene, t_vector factors)
{
	t_ray		ray;
	t_vector	vertical;
	t_vector	horizontal;
	t_vector	res;
	double		hv;

	hv = scene->camera.hview;
	vertical = vector_multi(scene->camera.up, \
		(t_vector){factors.y * hv, factors.y * hv, factors.y * hv});
	horizontal = vector_multi(scene->camera.right, \
		(t_vector){factors.x * scene->camera.wview, \
		factors.x * scene->camera.wview, factors.x * scene->camera.wview});
	res = vector_add(vertical, horizontal);
	res = vector_add(res, scene->camera.orientation);
	res = vector_add(res, scene->camera.viewpoint);
	ray.origin = scene->camera.viewpoint;
	ray.direction = vector_normal(vector_sub(res, ray.origin));
	return (ray);
}

t_vector	ft_ray_at(t_ray *ray, double t)
{
	return (vector_add(ray->origin, \
		vector_multi(ray->direction, (t_vector){t, t, t})));
}
