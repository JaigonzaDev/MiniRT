/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calculation_operations.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 12:12:01 by jaigonza          #+#    #+#             */
/*   Updated: 2026/04/05 12:14:14 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

double	vector_length(t_vector vec)
{
	return (sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z)));
}

t_vector	vector_normal(t_vector vec)
{
	t_vector	result;
	double		length;

	length = vector_length(vec);
	if (length == 0)
	{
		result.x = 0;
		result.y = 0;
		result.z = 0;
		return (result);
	}
	result.x = vec.x / length;
	result.y = vec.y / length;
	result.z = vec.z / length;
	return (result);
}

double	vector_dotproduct(t_vector vec1, t_vector vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vector	vector_crossproduct(t_vector vec1, t_vector vec2)
{
	return ((t_vector){(vec1.y * vec2.z) - (vec1.z * vec2.y),
		(vec1.z * vec2.x) - (vec1.x * vec2.z),
		(vec1.x * vec2.y) - (vec1.y * vec2.x)});
}
