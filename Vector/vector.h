#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}			t_vector;

// --- Vector basic operations ---
t_vector	vector_add(t_vector vec1, t_vector vec2);
t_vector	vector_sub(t_vector vec1, t_vector vec2);
t_vector	vector_multi(t_vector vec1, t_vector vec2);
t_vector	vector_div(t_vector vec1, t_vector vec2);

// --- Vector calculation operations ---
double		vector_length(t_vector vec);
t_vector	vector_normal(t_vector vec);
double		vector_dotproduct(t_vector vec1, t_vector vec2);
t_vector	vector_crossproduct(t_vector vec1, t_vector vec2);

#endif