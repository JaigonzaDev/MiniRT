/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 12:12:20 by jaigonza          #+#    #+#             */
/*   Updated: 2026/04/08 19:31:02 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "main.h"

void	ft_illuminate(t_scene *scene, t_hit *closest)
{
	t_color	color;

	color = ft_ambient_light(closest->color, scene->ambient.light_ratio);
	if (scene->light.brightness && !ft_is_shadowed(scene, closest))
		color = ft_color_add(color, ft_diffuse_light(&scene->light, closest,
					scene->light.brightness));
	closest->color = color;
}

t_color	ft_ambient_light(t_color color, double ratio)
{
	return (ft_color_mult(color, ratio));
}

bool	ft_is_shadowed(t_scene *scene, t_hit *closest)
{
	t_vector	light_dir;
	t_vector	light_dir_norm;
	t_ray		ray;
	t_hit		shadow_hit;
	double		light_distance;

	light_dir = vector_sub(scene->light.light_point, closest->point);
	light_distance = vector_length(light_dir);
	light_dir_norm = vector_normal(light_dir);
	ray.origin = vector_add(closest->point,
			vector_scale(light_dir_norm, EPSILON));
	ray.direction = light_dir_norm;
	shadow_hit.t = light_distance - EPSILON;
	shadow_hit.shape = NULL;
	if (ft_obj_hit(scene, &ray, &shadow_hit) && shadow_hit.t < light_distance)
		return (true);
	return (false);
}

t_color	ft_diffuse_light(t_light *light, t_hit *inter, double intensity)
{
	t_vector	light_dir;
	t_color		diff_color;
	double		cos_angle;
	double		diffuse_ratio;
	double		attenuation;

	light_dir = vector_sub(light->light_point, inter->point);
	attenuation = 90.0 / vector_length(light_dir);
	if (attenuation > 1.0)
		attenuation = 1.0;
	cos_angle = vector_dotproduct(vector_normal(inter->normal),
			vector_normal(light_dir));
	if (cos_angle < 0)
		cos_angle = 0;
	diffuse_ratio = intensity * cos_angle * attenuation;
	diff_color = ft_color_mult(inter->color, diffuse_ratio);
	return (diff_color);
}
