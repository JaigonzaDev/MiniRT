#ifndef INTERSECTION_H
# define INTERSECTION_H

# include "../render/render.h"
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

// Funciones de intersección
bool		sphere_intersect(t_sphere *sp, t_ray *ray, t_hit *hit_info);
bool		plane_intersect(t_plane *pl, t_ray *ray, t_hit *hit_info);
bool		cylinder_intersect(t_cylinder *cy, t_ray *ray, t_hit *hit_info);

#endif
