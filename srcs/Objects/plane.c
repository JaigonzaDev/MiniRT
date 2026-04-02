/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 12:00:00 by jaigonza          #+#    #+#             */
/*   Updated: 2026/04/02 12:00:00 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "intersection.h"

static bool	set_plane_hit(t_plane *plane, t_ray *ray, t_hit *pixel, double t)
{
	double	denom;

	denom = vector_dotproduct(ray->direction, plane->normalized);
	pixel->t = t;
	pixel->color.r = (int)plane->rgb.x;
	pixel->color.g = (int)plane->rgb.y;
	pixel->color.b = (int)plane->rgb.z;
	pixel->shape = plane;
	pixel->point = ft_ray_at(ray, pixel->t);
	if (denom < 0)
		pixel->normal = plane->normalized;
	else
		pixel->normal = vector_multi(plane->normalized, \
			(t_vector){-1, -1, -1});
	return (true);
}

bool	hit_plane(t_plane *plane, t_ray *ray, t_hit *pixel)
{
	t_vector	plane_to_ray;
	t_equation	equation;
	double		denominator;

	denominator = vector_dotproduct(ray->direction, plane->normalized);
	if (fabs(denominator) > EPSILON)
	{
		plane_to_ray = vector_sub(plane->point, ray->origin);
		equation.t1 = vector_dotproduct(plane_to_ray, \
			plane->normalized) / denominator;
		if (equation.t1 > EPSILON)
			return (set_plane_hit(plane, ray, pixel, equation.t1));
	}
	return (false);
}
