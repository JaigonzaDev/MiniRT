#include "../render/render.h"

bool hit_plane(t_plane *plane, t_ray *ray, t_hit *pixel)
{
	t_vector		plane_to_ray;
	t_equation	equation;
	double		denominator;

	// Check if the ray is not parallel to the plane
	denominator = vector_dotproduct(ray->direction, plane->normalized);
	if (fabs(denominator) > EPSILON)
	{
		plane_to_ray = vector_sub(plane->point, ray->origin);
		equation.t1 = vector_dotproduct(plane_to_ray, plane->normalized) / denominator;
		if (equation.t1 > EPSILON)
		{
			pixel->t = equation.t1;
			pixel->color.r = (int)plane->rgb.x;
			pixel->color.g = (int)plane->rgb.y;
			pixel->color.b = (int)plane->rgb.z;
			pixel->shape = plane;
			pixel->point = ft_ray_at(ray, pixel->t);
			if (denominator < 0)
				pixel->normal = plane->normalized;
			else
				pixel->normal = vector_multi(plane->normalized, (t_vector){-1, -1, -1});
			return (true);
		}
	}
	return (false);
}