#ifndef INTERSECTION_H
# define INTERSECTION_H

# include "render.h"
# include <math.h>
# include <stdbool.h>

// Estructura para ecuaciones cuadráticas
typedef struct s_equation
{
	double	a;
	double	b;
	double	c;
	double	t1;
	double	t2;
}	t_equation;

// Funciones auxiliares
int			solve(t_equation *eq);
t_plane		plane_from_numbers(t_vector center, t_vector normal, t_color color);

double		verify_intersections(t_cylinder *cy, t_ray *r, \
			t_equation *eq, t_hit *hit_info);
bool		check_caps(t_cylinder *cy, t_vector cap, t_hit *in, double t);
bool		check_walls(t_cylinder *cy, t_hit *in, double t);
double		cap_intersection(t_cylinder *cy, t_ray *ray, t_vector cap);

// Funciones de intersección
bool		sphere_intersect(t_sphere *sp, t_ray *ray, t_hit *hit_info);
bool		plane_intersect(t_plane *pl, t_ray *ray, t_hit *hit_info);
bool		hit_cylinder(t_cylinder *cyl, t_ray *ray, t_hit *pixel);

#endif
