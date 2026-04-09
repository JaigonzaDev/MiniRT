/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 12:13:57 by jaigonza          #+#    #+#             */
/*   Updated: 2026/04/09 18:53:06 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "libft.h"
# include "vector.h"
# include <math.h>

typedef struct s_camera
{
	t_vector	center;
	t_vector	normal;
	double		fov;
}				t_camera;
typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}				t_ray;
typedef struct s_viewport
{
	t_vector	up;
	t_vector	right;
	double		hview;
	double		wview;
}				t_viewport;

void		init_viewport(t_camera *camera, t_viewport *viewport);
t_vector	canvas_to_viewport(int x, int y);
t_ray		cast_ray(t_camera *camera, t_viewport *viewport, t_vector factors);
t_vector	ray_at(t_ray *ray, double t);
t_vector	vector_scale(t_vector vec, double scalar);

#endif
