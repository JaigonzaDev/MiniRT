/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 12:13:10 by jaigonza          #+#    #+#             */
/*   Updated: 2026/04/08 18:37:35 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"

static void	setup_cylinder_equation(t_cylinder *cyl, t_ray *r,
			t_equation *eq)
{
	t_vector	cy_to_ray;
	double		dot_r_norm;
	double		dot_cy_norm;

	eq->t1 = -1;
	eq->t2 = -1;
	cy_to_ray = vector_sub(r->origin, cyl->center);
	dot_r_norm = vector_dotproduct(r->direction, cyl->normalized);
	dot_cy_norm = vector_dotproduct(cy_to_ray, cyl->normalized);
	eq->a = vector_dotproduct(r->direction, r->direction) - pow(dot_r_norm, 2);
	eq->b = 2 * (vector_dotproduct(r->direction, cy_to_ray)
			- (dot_r_norm * dot_cy_norm));
	eq->c = vector_dotproduct(cy_to_ray, cy_to_ray)
		- pow(dot_cy_norm, 2) - pow(cyl->diameter / 2.0, 2);
	solve(eq);
}

static void	apply_cylinder_hit(t_cylinder *cyl, t_ray *ray, t_hit *pixel,
			double t)
{
	t_vector	base_to_point;
	double		projection;
	t_vector	axis_point;
	t_vector	normal;

	pixel->t = t;
	pixel->color.r = (int)cyl->rgb.x;
	pixel->color.g = (int)cyl->rgb.y;
	pixel->color.b = (int)cyl->rgb.z;
	pixel->shape = cyl;
	pixel->point = ft_ray_at(ray, pixel->t);
	base_to_point = vector_sub(pixel->point, cyl->center);
	projection = vector_dotproduct(base_to_point, cyl->normalized);
	if (fabs(projection) <= EPSILON)
		normal = vector_multi(cyl->normalized, (t_vector){-1, -1, -1});
	else if (fabs(projection - cyl->height) <= EPSILON)
		normal = cyl->normalized;
	else
	{
		axis_point = vector_add(cyl->center,
				vector_scale(cyl->normalized, projection));
		normal = vector_normal(vector_sub(pixel->point, axis_point));
	}
	if (vector_dotproduct(normal, ray->direction) > 0)
		normal = vector_multi(normal, (t_vector){-1, -1, -1});
	pixel->normal = normal;
}

bool	hit_cylinder(t_cylinder *cyl, t_ray *ray, t_hit *pixel)
{
	double		t;
	t_equation	eq;

	setup_cylinder_equation(cyl, ray, &eq);
	pixel->ray = *ray;
	t = verify_intersections(cyl, ray, &eq, pixel);
	if (t > EPSILON)
	{
		apply_cylinder_hit(cyl, ray, pixel, t);
		return (true);
	}
	return (false);
}
