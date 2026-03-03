#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdio.h>
#include "../vector/vector.h"

typedef struct s_sphere
{
    char *id;
    t_vector center;
    double diameter;
    t_vector rgb;
    struct s_sphere *next;
} t_sphere;

typedef struct s_plane
{
    char *id;
    t_vector point;
    t_vector normalized;
    t_vector rgb;
    struct s_plane *next;
} t_plane;

typedef struct s_cylinder
{
    char *id;
    t_vector center;
    t_vector normalized;
    double diameter;
    double height;
    t_vector rgb;
    struct s_cylinder *next;
} t_cylinder;

typedef struct s_equation
{
	double	a;
	double	b;
	double	c;
	double	t1;
	double	t2;
}			t_equation;

double solve(t_equation *eq);

#endif