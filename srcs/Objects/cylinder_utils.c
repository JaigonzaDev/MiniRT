
#include "intersection.h"

bool	check_caps(t_cylinder *cy, t_vector cap, t_hit *inter, double t)
{
	double		len;
	t_vector	point;

	if (t < EPSILON || t > inter->t)
		return (false);
	point = ft_ray_at(&inter->ray, t);
	len = vector_length(vector_sub(point, cap));
	if (len <= (cy->diameter / 2.0))
	{
		inter->t = t;
		return (true);
	}
	return (false);
}

bool	check_walls(t_cylinder *cy, t_hit *inter, double t, t_vector cap_b)
{
	t_vector	point;
	t_vector	co;
	t_vector	a;
	double		m;
	double		len;

	if (t < EPSILON || t > inter->t)
		return (false);
	point = ft_ray_at(&inter->ray, t);
	co = vector_sub(inter->ray.origin, cap_b);
	m = vector_dotproduct(inter->ray.direction, cy->normalized) * t + \
		vector_dotproduct(co, cy->normalized);
	a = vector_add(cap_b, vector_multi(cy->normalized, (t_vector){m, m, m}));
	len = vector_length(vector_sub(point, a));
	if (m >= 0 && m <= cy->height && len <= (cy->diameter / 2.0) + EPSILON)
	{
		inter->t = t;
		return (true);
	}
	return (false);
}

double	cap_intersection(t_cylinder *cy, t_ray *ray, t_vector cap)
{
	double		denominator;
	t_vector	plane_to_ray;
	double		t;

	denominator = vector_dotproduct(ray->direction, cy->normalized);
	if (fabs(denominator) > EPSILON)
	{
		plane_to_ray = vector_sub(cap, ray->origin);
		t = vector_dotproduct(plane_to_ray, cy->normalized) / denominator;
		return (t);
	}
	return (-1);
}

double	verify_intersections(t_cylinder *cy, t_ray *ray, \
		t_equation *eq, t_vector *caps)
{
	double	t3;
	double	t4;
	t_hit	temp;

	t3 = cap_intersection(cy, ray, caps[0]);
	t4 = cap_intersection(cy, ray, caps[1]);
	temp.t = INFINITY;
	temp.ray = *ray;
	check_walls(cy, &temp, eq->t1, caps[0]);
	check_walls(cy, &temp, eq->t2, caps[0]);
	check_caps(cy, caps[0], &temp, t3);
	check_caps(cy, caps[1], &temp, t4);
	if (temp.t == INFINITY)
		return (0);
	return (temp.t);
}
