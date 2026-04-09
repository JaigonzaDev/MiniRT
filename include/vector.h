/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 12:13:31 by jaigonza          #+#    #+#             */
/*   Updated: 2026/04/09 18:52:32 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "libft.h"
# include <math.h>

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}			t_vector;

t_vector	vector_add(t_vector vec1, t_vector vec2);
t_vector	vector_sub(t_vector vec1, t_vector vec2);
t_vector	vector_multi(t_vector vec1, t_vector vec2);
t_vector	vector_scale(t_vector vec, double scalar);

double		vector_length(t_vector vec);
t_vector	vector_normal(t_vector vec);
double		vector_dotproduct(t_vector vec1, t_vector vec2);
t_vector	vector_crossproduct(t_vector vec1, t_vector vec2);

#endif
