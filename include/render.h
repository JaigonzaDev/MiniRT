/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 12:00:00 by jaigonza          #+#    #+#             */
/*   Updated: 2026/04/02 12:00:00 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef RENDER_H
# define RENDER_H

# include "vector.h"
# include "objects.h"
# include "properties.h"
# include "graph.h"
# include <math.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <mlx.h>

struct s_scene;
typedef struct s_scene	t_scene;

# define PI 3.1415926535
# define RADIANS(deg) ((deg * PI) / 180.0)
# define EPSILON 0.0001
# define MIN(a, b) ((a) < (b) ? (a) : (b))
# define MAX(a, b) ((a) > (b) ? (a) : (b))

# ifdef __APPLE__
#  define WIDTH 1440
# else
#  define WIDTH 1920
# endif

# define RATIO (16.0/9.0)
# define HEIGHT (WIDTH/RATIO)

# define UPGUIDE (t_vector){0.0, 1.0, 0.0}
# define VEC_EPSILON (t_vector){EPSILON, EPSILON, EPSILON}

typedef struct s_color
{
	int	t;
	int	r;
	int	g;
	int	b;
}	t_color;

# define WHITE (t_color){0, 255, 255, 255}
# define BLACK (t_color){0, 0, 0, 0}

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
int			ft_render(t_scene *scene);
int			render(t_scene scene);
void		ft_put_pixel(t_scene *scene, t_color color, int x, int y);
bool		ft_obj_hit(t_scene *scene, t_ray *ray, t_hit *pixel);
bool		hit_sphere(t_sphere *sphere, t_ray *ray, t_hit *pixel);
bool		hit_plane(t_plane *plane, t_ray *ray, t_hit *pixel);
bool		hit_cylinder(t_cylinder *cyl, t_ray *ray, t_hit *pixel);

// Funciones de viewport y rayos
void		ft_init_viewport(t_scene *scene);
t_vector	ft_canvas_to_viewport(int x, int y);
t_ray		ft_cast_ray(t_scene *scene, t_vector factors);
t_vector	ft_ray_at(t_ray *ray, double t);

// Funciones de color
t_color		ft_color_create(int r, int g, int b);
t_color		ft_color_add(t_color c1, t_color c2);
t_color		ft_color_mult(t_color color, double k);
int			ft_clamp(int value, int min, int max);

// Funciones de iluminación
void		ft_illuminate(t_scene *scene, t_hit *closest);
t_color		ft_ambient_light(t_color color, double ratio);
t_color		ft_diffuse_light(t_light *light, t_hit *inter, double intensity);
bool		ft_is_shadowed(t_scene *scene, t_hit *closest);

// Función para guardar imagen
void		ft_save_image(t_scene *scene, char *filename);

#endif
