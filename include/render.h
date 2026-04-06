/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 12:13:34 by jaigonza          #+#    #+#             */
/*   Updated: 2026/04/06 21:14:33 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "libft.h"
# include "vector.h"
# include "objects.h"
# include "properties.h"
# include "graph.h"
# include <math.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <mlx.h>

struct	s_scene;

# ifndef PI
#  define PI 3.1415926535
# endif
# define EPSILON 0.0001

# ifdef __APPLE__
#  define WIDTH 1440
#  define HEIGHT 810
# else
#  define WIDTH 1920
#  define HEIGHT 1080
# endif

# define RATIO 1.77777777778

typedef struct s_color
{
	int	t;
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}	t_ray;

typedef struct s_hit
{
	void		*shape;
	int			shape_type;
	t_ray		ray;
	t_vector	point;
	t_vector	normal;
	t_color		color;
	double		t;
}	t_hit;

// Funciones de render
int			ft_render(struct s_scene *scene);
void		ft_put_pixel(struct s_scene *scene, t_color color, int x, int y);
bool		ft_obj_hit(struct s_scene *scene, t_ray *ray, t_hit *pixel);
bool		hit_sphere(t_sphere *sphere, t_ray *ray, t_hit *pixel);
bool		hit_plane(t_plane *plane, t_ray *ray, t_hit *pixel);
bool		hit_cylinder(t_cylinder *cyl, t_ray *ray, t_hit *pixel);

// Funciones de viewport y rayos
void		ft_init_viewport(struct s_scene *scene);
t_vector	ft_canvas_to_viewport(int x, int y);
t_ray		ft_cast_ray(struct s_scene *scene, t_vector factors);
t_vector	ft_ray_at(t_ray *ray, double t);

// Funciones de color
t_color		ft_color_create(int r, int g, int b);
t_color		ft_color_add(t_color c1, t_color c2);
t_color		ft_color_mult(t_color color, double k);
int			ft_clamp(int value, int min, int max);

// Funciones de iluminación
void		ft_illuminate(struct s_scene *scene, t_hit *closest);
t_color		ft_ambient_light(t_color color, double ratio);
t_color		ft_diffuse_light(t_light *light, t_hit *inter, double intensity);
bool		ft_is_shadowed(struct s_scene *scene, t_hit *closest);

#endif
