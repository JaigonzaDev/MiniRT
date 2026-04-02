#include "intersection.h"
#include "main.h"

bool	sphere_intersect(t_sphere *sp, t_ray *ray, t_hit *hit_info)
{
	t_vector	sphere_to_ray;
	t_equation	eq;

	eq.t1 = -1.0f;
	sphere_to_ray = vector_sub(ray->origin, sp->center);
	eq.a = vector_dotproduct(ray->direction, ray->direction);
	eq.b = 2.0f * vector_dotproduct(sphere_to_ray, ray->direction);
	eq.c = vector_dotproduct(sphere_to_ray, sphere_to_ray) - \
		pow(sp->diameter / 2.0, 2);
	if (solve(&eq) > 0 && (eq.t1 > EPSILON || eq.t2 > EPSILON))
	{
		if (eq.t1 > EPSILON)
			hit_info->t = eq.t1;
		else
			hit_info->t = eq.t2;
		hit_info->color = ft_color_create((int)sp->rgb.x, \
			(int)sp->rgb.y, (int)sp->rgb.z);
		hit_info->point = ft_ray_at(ray, hit_info->t);
		hit_info->normal = vector_normal(vector_sub(hit_info->point, \
			sp->center));
		return (true);
	}
	return (false);
}
