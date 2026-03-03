#include "intersection.h"
#include "../main.h"

bool	check_caps(t_cylinder *cy, t_vector cap, t_hit *inter, double t)
{
	double	len;
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
	t_vector	base_to_point;
	double	m;
	double	len;

	point = ft_ray_at(&inter->ray, t);
	co = vector_sub(inter->ray.origin, cy->center);
	m = vector_dotproduct(inter->ray.direction, cy->normalized) * t + 
		vector_dotproduct(co, cy->normalized);
	base_to_point = vector_scale(cy->normalized, m);
	len = vector_length(vector_sub(point, vector_add(cy->center, base_to_point)));
	m -= EPSILON;
	len -= EPSILON;
	if (m >= 0 && m <= cy->height && len <= (cy->diameter / 2.0) 
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

	plane = plane_from_numbers(cap, cy->normalized, BLACK);
	if (plane_intersect(&plane, ray, &inter))
		return (inter.t);
	return (-1);
}

double	verify_intersections(t_cylinder *cy, t_ray *ray, 
	t_equation *eq, t_hit *hit_info)
{
	double	t3;
	double	t4;
	t_vector	cap_top;

	cap_top = vector_add(cy->center, vector_scale(cy->normalized, cy->height));
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

bool	cylinder_intersect(t_cylinder *cy, t_ray *ray, t_hit *hit_info)
{
	double		t;
	t_vector	cy_to_ray;
	t_equation	eq;

	eq.t1 = -1;
	eq.t2 = -1;
	cy_to_ray = vector_sub(ray->origin, cy->center);
	eq.a = vector_dotproduct(ray->direction, ray->direction) - 
		pow(vector_dotproduct(ray->direction, cy->normalized), 2);
	eq.b = 2 * (vector_dotproduct(ray->direction, cy_to_ray) - 
		(vector_dotproduct(ray->direction, cy->normalized) * 
		vector_dotproduct(cy_to_ray, cy->normalized)));
	eq.c = vector_dotproduct(cy_to_ray, cy_to_ray) - 
		pow(vector_dotproduct(cy_to_ray, cy->normalized), 2) - 
		pow(cy->diameter / 2.0, 2);
	solve(&eq);
	if (eq.t1 <= 0 && eq.t2 <= 0)
		return (false);
	t = verify_intersections(cy, ray, &eq, hit_info);
	if (t > 0.0f)
	{
		hit_info->t = t;
		hit_info->color = ft_color_create((int)cy->rgb.x, (int)cy->rgb.y, (int)cy->rgb.z);
		hit_info->point = ft_ray_at(ray, hit_info->t);
		// Calcular normal del cilindro
		t_vector base_to_point = vector_sub(hit_info->point, cy->center);
		double projection = vector_dotproduct(base_to_point, cy->normalized);
		t_vector axis_point = vector_add(cy->center, vector_scale(cy->normalized, projection));
		hit_info->normal = vector_normal(vector_sub(hit_info->point, axis_point));
		return (true);
	}
	return (false);
}
