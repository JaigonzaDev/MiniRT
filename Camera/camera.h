/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Created: 2026/02/24 00:00:00 by carlos            #+#    #+#             */
/*   Updated: 2026/02/24 00:00:00 by carlos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "../Vector/vector.h"
# include <math.h>

/* ************************************************************************** */
/*                                  MACROS                                    */
/* ************************************************************************** */

# define PI 3.1415926535
# define RADIANS(deg) ((deg * PI) / 180.0)

# ifdef __APPLE__
#  define WIDTH 1440
# else
#  define WIDTH 1920
# endif

# define RATIO (16.0/9.0)
# define HEIGHT (WIDTH/RATIO)

# define UPGUIDE (t_vector){0.0, 1.0, 0.0}

/* ************************************************************************** */
/*                                 STRUCTURES                                 */
/* ************************************************************************** */

/**
 * @brief Describes how the camera is positioned in the scene
 *
 * @param center The center of the camera
 * @param normal The direction of the camera (normalized)
 * @param fov The camera's Field Of View (in degrees)
 */
typedef struct s_camera
{
	t_vector	center;
	t_vector	normal;
	double		fov;
}				t_camera;

/**
 * @brief A scene's ray
 *
 * @param origin The origin of the ray
 * @param direction The direction of the ray (normalized)
 */
typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}				t_ray;

/**
 * @brief Viewport data (what the camera can see)
 *
 * @param up The viewport up vector
 * @param right The viewport right vector
 * @param hview The height of the viewport
 * @param wview The width of the viewport
 */
typedef struct s_viewport
{
	t_vector	up;
	t_vector	right;
	double		hview;
	double		wview;
}				t_viewport;

/* ************************************************************************** */
/*                              FUNCTION DECLARATIONS                         */
/* ************************************************************************** */

/**
 * @brief Initializes the viewport (what the camera can see).
 * The viewport will be supported by 3 vectors: up, right and forward.
 * Together, those vectors can return any point on the plane.
 *
 * @param camera The camera struct
 * @param viewport The viewport struct to initialize
 */
void		init_viewport(t_camera *camera, t_viewport *viewport);

/**
 * @brief Converts a pixel in x (0 to width - 1) and y (0 to height - 1) to
 * viewport x and viewport y factors (between -1 and 1).
 * These factors are used with the viewport vectors to access any point.
 *
 * @param x The pixel's x coordinate
 * @param y The pixel's y coordinate
 * @return t_vector The x and y viewport factors (z is unused)
 */
t_vector	canvas_to_viewport(int x, int y);

/**
 * @brief Casts an infinite ray in space from the camera with the direction
 * of one of the viewport's point.
 *
 * @param camera The camera struct
 * @param viewport The viewport struct
 * @param factors The viewport factors from canvas_to_viewport
 * @return t_ray The casted ray
 */
t_ray		cast_ray(t_camera *camera, t_viewport *viewport, t_vector factors);

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
t_vector	ray_at(t_ray *ray, double t);

/**
 * @brief Scales a vector by a scalar value
 *
 * @param vec The vector to scale
 * @param scalar The scalar value
 * @return t_vector The scaled vector
 */
t_vector	vector_scale(t_vector vec, double scalar);

#endif
