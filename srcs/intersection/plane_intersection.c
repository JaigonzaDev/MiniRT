#include "intersection.h"
#include "main.h"

bool	plane_intersect(t_plane *pl, t_ray *ray, t_hit *hit_info)
{
	t_vector	plane_to_ray;
	t_equation	eq;

	if (vector_dotproduct(ray->direction, pl->normalized) != 0.0)
	{
		plane_to_ray = vector_sub(ray->origin, pl->point);
		eq.a = 0;
		eq.b = vector_dotproduct(ray->direction, pl->normalized);
		eq.c = vector_dotproduct(plane_to_ray, pl->normalized);
		solve(&eq);
		if (eq.t1 > EPSILON)
		{
			hit_info->t = eq.t1;
			hit_info->color = ft_color_create((int)pl->rgb.x, \
				(int)pl->rgb.y, (int)pl->rgb.z);
			hit_info->point = ft_ray_at(ray, hit_info->t);
			hit_info->normal = vector_normal(pl->normalized);
			return (true);
		}
	}
	return (false);
}
