/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 12:13:03 by jaigonza          #+#    #+#             */
/*   Updated: 2026/04/05 12:14:08 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"

bool	hit_sphere(t_sphere *sphere, t_ray *ray, t_hit *pixel)
{
	t_vector	sphere_to_ray;
	t_equation	eq;

	eq.t1 = -1.0f;
	sphere_to_ray = vector_sub(ray->origin, sphere->center);
	eq.a = vector_dotproduct(ray->direction, ray->direction);
	eq.b = 2.0f * vector_dotproduct(sphere_to_ray, ray->direction);
	eq.c = vector_dotproduct(sphere_to_ray, sphere_to_ray)
		- pow(sphere->diameter / 2.0, 2);
	if (solve(&eq) > 0 && (eq.t1 > EPSILON || eq.t2 > EPSILON))
	{
		if (eq.t1 > EPSILON)
			pixel->t = eq.t1;
		else
			pixel->t = eq.t2;
		pixel->color.r = (int)sphere->rgb.x;
		pixel->color.g = (int)sphere->rgb.y;
		pixel->color.b = (int)sphere->rgb.z;
		pixel->shape = sphere;
		pixel->point = ft_ray_at(ray, pixel->t);
		pixel->normal = vector_normal(vector_sub(pixel->point,
					sphere->center));
		return (true);
	}
	return (false);
}
