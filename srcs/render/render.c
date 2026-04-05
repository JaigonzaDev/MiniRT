/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 12:12:07 by jaigonza          #+#    #+#             */
/*   Updated: 2026/04/05 12:14:14 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "main.h"

static bool	update_hit_if_closer(t_hit *temp, t_hit *pixel, double *closest)
{
	if (temp->t < *closest)
	{
		*closest = temp->t;
		*pixel = *temp;
		return (true);
	}
	return (false);
}

static bool	check_spheres(t_sphere *sp, t_ray *ray, t_hit *pixel,
			double *closest)
{
	bool	hit;
	t_hit	temp;

	hit = false;
	while (sp)
	{
		if (hit_sphere(sp, ray, &temp))
			hit |= update_hit_if_closer(&temp, pixel, closest);
		sp = sp->next;
	}
	return (hit);
}

static bool	check_planes(t_plane *pl, t_ray *ray, t_hit *pixel,
			double *closest)
{
	bool	hit;
	t_hit	temp;

	hit = false;
	while (pl)
	{
		if (hit_plane(pl, ray, &temp))
			hit |= update_hit_if_closer(&temp, pixel, closest);
		pl = pl->next;
	}
	return (hit);
}

static bool	check_cylinders(t_cylinder *cy, t_ray *ray, t_hit *pixel,
			double *closest)
{
	bool	hit;
	t_hit	temp;

	hit = false;
	while (cy)
	{
		if (hit_cylinder(cy, ray, &temp))
			hit |= update_hit_if_closer(&temp, pixel, closest);
		cy = cy->next;
	}
	return (hit);
}

bool	ft_obj_hit(t_scene *scene, t_ray *ray, t_hit *pixel)
{
	bool	hit_anything;
	double	closest_so_far;

	hit_anything = false;
	closest_so_far = pixel->t;
	hit_anything |= check_spheres(scene->sphere, ray, pixel, &closest_so_far);
	hit_anything |= check_planes(scene->plane, ray, pixel, &closest_so_far);
	hit_anything |= check_cylinders(scene->cylinder, ray, pixel,
			&closest_so_far);
	return (hit_anything);
}
