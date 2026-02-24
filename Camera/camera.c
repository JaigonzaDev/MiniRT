/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Created: 2026/02/24 00:00:00 by carlos            #+#    #+#             */
/*   Updated: 2026/02/24 00:00:00 by carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"

/**
 * @brief Scales a vector by a scalar value
 *
 * @param vec The vector to scale
 * @param scalar The scalar value
 * @return t_vector The scaled vector
 */
t_vector	vector_scale(t_vector vec, double scalar)
{
	return ((t_vector){vec.x * scalar, vec.y * scalar, vec.z * scalar});
}

/**
 * @brief Initializes the viewport (what the camera can see).
 * The viewport will be supported by 3 vectors: up, right and forward.
 * Together, those vectors can return any point on the plane.
 *
 * The viewport is calculated based on the camera's field of view and
 * the aspect ratio of the screen. The up and right vectors are calculated
 * to be perpendicular to the camera's direction (normal).
 *
 * @param camera The camera struct
 * @param viewport The viewport struct to initialize
 */
void	init_viewport(t_camera *camera, t_viewport *viewport)
{
	viewport->wview = tan(RADIANS(camera->fov / 2.0));
	viewport->hview = viewport->wview / RATIO;
	viewport->right = vector_normal(vector_crossproduct(camera->normal,
				UPGUIDE));
	viewport->up = vector_normal(vector_crossproduct(camera->normal,
				viewport->right));
	viewport->right = vector_normal(vector_crossproduct(camera->normal,
				viewport->up));
}

/**
 * @brief Converts a pixel in x (0 to width - 1) and y (0 to height - 1) to
 * viewport x and viewport y factors (between -1 and 1).
 * These factors are used with the viewport vectors to access any point.
 *
 * @param x The pixel's x coordinate
 * @param y The pixel's y coordinate
 * @return t_vector The x and y viewport factors (z is unused)
 */
t_vector	canvas_to_viewport(int x, int y)
{
	t_vector	converted;
	double		width;
	double		height;

	width = WIDTH;
	height = HEIGHT;
	converted.x = ((2.0 * x) / width) - 1;
	converted.y = ((2.0 * y) / height) - 1;
	converted.z = 0;
	return (converted);
}

/**
 * @brief Casts an infinite ray in space from the camera with the direction
 * of one of the viewport's point.
 *
 * The ray is calculated by scaling the viewport's up and right vectors by
 * the given factors, adding them together with the camera's normal vector
 * and the camera's center position to get the target point.
 * The ray's direction is the normalized vector from the origin to this point.
 *
 * @param camera The camera struct
 * @param viewport The viewport struct
 * @param factors The viewport factors from canvas_to_viewport
 * @return t_ray The casted ray
 */
t_ray	cast_ray(t_camera *camera, t_viewport *viewport, t_vector factors)
{
	t_ray		ray;
	t_vector	vertical;
	t_vector	horizontal;
	t_vector	res;

	vertical = vector_scale(viewport->up, factors.y * viewport->hview);
	horizontal = vector_scale(viewport->right, factors.x * viewport->wview);
	res = vector_add(vertical, horizontal);
	res = vector_add(res, camera->normal);
	res = vector_add(res, camera->center);
	ray.origin = camera->center;
	ray.direction = vector_normal(vector_sub(res, ray.origin));
	return (ray);
}

/**
 * @brief Returns the point in the given ray with t direction vectors.
 * A ray's equation is given by: P = O + tD
 *
 * P - The point at t direction vectors
 * O - The ray's origin
 * t - Distance factor
 * D - The ray's direction
 *
 * @param ray The casted ray
 * @param t The distance factor
 * @return t_vector The point at t
 */
t_vector	ray_at(t_ray *ray, double t)
{
	return (vector_add(ray->origin, vector_scale(ray->direction, t)));
}
