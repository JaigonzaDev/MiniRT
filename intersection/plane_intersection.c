/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iremoztimur <iremoztimur@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:26:41 by iremoztimur       #+#    #+#             */
/*   Updated: 2024/02/12 16:26:57 by iremoztimur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include "../main.h"

bool	plane_intersect(t_plane *pl, t_ray *ray, t_hit *hit_info)
{
	t_vector	plane_to_ray;
	t_equation	equation;

	// Check if the ray is not parallel to the plane
	if (vector_dotproduct(ray->direction, pl->normalized) != 0.0)
	{
		plane_to_ray = vector_sub(ray->origin, pl->point);
		equation.a = 0;
		equation.b = vector_dotproduct(ray->direction, pl->normalized);
		equation.c = vector_dotproduct(plane_to_ray, pl->normalized);
		solve(&equation);
		if (equation.t1 > EPSILON)
		{
			hit_info->t = equation.t1;
			hit_info->color = ft_color_create((int)pl->rgb.x, (int)pl->rgb.y, (int)pl->rgb.z);
			hit_info->point = ft_ray_at(ray, hit_info->t);
			hit_info->normal = vector_normal(pl->normalized);
			return (true);
		}
	}
	return (false);
}
