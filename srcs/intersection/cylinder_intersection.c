#include "intersection.h"
#include "main.h"

static void	setup_cy_equation(t_cylinder *cy, t_ray *ray,
			t_vector *cy_to_ray, t_equation *eq)
{
	eq->t1 = -1;
	eq->t2 = -1;
	*cy_to_ray = vector_sub(ray->origin, cy->center);
	eq->a = vector_dotproduct(ray->direction, ray->direction)
		- pow(vector_dotproduct(ray->direction, cy->normalized), 2);
	eq->b = 2 * (vector_dotproduct(ray->direction, *cy_to_ray)
			- (vector_dotproduct(ray->direction, cy->normalized)
				* vector_dotproduct(*cy_to_ray, cy->normalized)));
	eq->c = vector_dotproduct(*cy_to_ray, *cy_to_ray)
		- pow(vector_dotproduct(*cy_to_ray, cy->normalized), 2)
		- pow(cy->diameter / 2.0, 2);
	solve(eq);
}

static bool	apply_cy_hit(t_cylinder *cy, t_ray *ray, t_hit *hit_info, double t)
{
	t_vector	base_to_point;
	double		projection;
	t_vector	axis_point;

	hit_info->t = t;
	hit_info->color = ft_color_create((int)cy->rgb.x, (int)cy->rgb.y,
			(int)cy->rgb.z);
	hit_info->point = ft_ray_at(ray, hit_info->t);
	base_to_point = vector_sub(hit_info->point, cy->center);
	projection = vector_dotproduct(base_to_point, cy->normalized);
	axis_point = vector_add(cy->center,
			vector_scale(cy->normalized, projection));
	hit_info->normal = vector_normal(vector_sub(hit_info->point, axis_point));
	return (true);
}

bool	cylinder_intersect(t_cylinder *cy, t_ray *ray, t_hit *hit_info)
{
	double		t;
	t_vector	cy_to_ray;
	t_equation	eq;

	setup_cy_equation(cy, ray, &cy_to_ray, &eq);
	if (eq.t1 <= 0 && eq.t2 <= 0)
		return (false);
	t = verify_intersections(cy, ray, &eq, hit_info);
	if (t > 0.0f)
		return (apply_cy_hit(cy, ray, hit_info, t));
	return (false);
}
