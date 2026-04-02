/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_basic_operations.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 12:00:00 by jaigonza          #+#    #+#             */
/*   Updated: 2026/04/02 12:00:00 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "vector.h"

t_vector	vector_scale(t_vector vec, double scalar)
{
	return ((t_vector){vec.x * scalar, vec.y * scalar, vec.z * scalar});
}

t_vector	vector_add(t_vector vec1, t_vector vec2)
{
	return ((t_vector){vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z});
}

t_vector	vector_sub(t_vector vec1, t_vector vec2)
{
	return ((t_vector){vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z});
}

t_vector	vector_multi(t_vector vec1, t_vector vec2)
{
	return ((t_vector){vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z});
}

t_vector	vector_div(t_vector vec1, t_vector vec2)
{
	return ((t_vector){vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z});
}
