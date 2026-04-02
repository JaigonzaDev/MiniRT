/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 12:00:00 by jaigonza          #+#    #+#             */
/*   Updated: 2026/04/02 12:00:00 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "intersection.h"
#include "main.h"

bool	check_caps(t_cylinder *cy, t_vector cap, t_hit *inter, double t)
{
	double		len;
	t_vector	point;

	point = ft_ray_at(&inter->ray, t);
	len = vector_length(vector_sub(point, cap));
	len += EPSILON;
	if (len <= (cy->diameter / 2.0) && t > EPSILON && t < inter->t)
	{
		inter->t = t;
		return (true);
	}
	return (false);
}

bool	check_walls(t_cylinder *cy, t_hit *inter, double t)
{
	t_vector	point;
	t_vector	co;
	t_vector	bp;
	double		m;
	double		len;

	point = ft_ray_at(&inter->ray, t);
	co = vector_sub(inter->ray.origin, cy->center);
	m = vector_dotproduct(inter->ray.direction, cy->normalized) * t + \
		vector_dotproduct(co, cy->normalized);
	bp = vector_scale(cy->normalized, m);
	len = vector_length(vector_sub(point, vector_add(cy->center, bp)));
	m -= EPSILON;
	len -= EPSILON;
	if (m >= 0 && m <= cy->height && len <= (cy->diameter / 2.0) \
		&& t > EPSILON && t < inter->t)
	{
		inter->t = t;
		return (true);
	}
	return (false);
}

double	cap_intersection(t_cylinder *cy, t_ray *ray, t_vector cap)
{
	t_plane	plane;
	t_hit	inter;

	plane = plane_from_numbers(cap, cy->normalized, ft_color_create(0, 0, 0));
	if (plane_intersect(&plane, ray, &inter))
		return (inter.t);
	return (-1);
}

double	verify_intersections(t_cylinder *cy, t_ray *ray, \
	t_equation *eq, t_hit *hit_info)
{
	double		t3;
	double		t4;
	t_vector	cap_top;

	cap_top = vector_add(cy->center, \
		vector_scale(cy->normalized, cy->height));
	t3 = cap_intersection(cy, ray, cy->center);
	t4 = cap_intersection(cy, ray, cap_top);
	hit_info->t = INFINITY;
	hit_info->ray = *ray;
	check_walls(cy, hit_info, eq->t1);
	check_walls(cy, hit_info, eq->t2);
	check_caps(cy, cy->center, hit_info, t3);
	check_caps(cy, cap_top, hit_info, t4);
	if (hit_info->t == INFINITY)
		return (0);
	return (hit_info->t);
}
