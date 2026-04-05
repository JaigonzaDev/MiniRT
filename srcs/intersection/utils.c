/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 12:13:14 by jaigonza          #+#    #+#             */
/*   Updated: 2026/04/05 12:14:06 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include "main.h"

/*
** Resuelve una ecuación cuadrática: ax² + bx + c = 0
** Retorna el número de soluciones reales (0, 1, o 2)
** Las soluciones se almacenan en eq->t1 y eq->t2
*/
int	solve(t_equation *eq)
{
	double	discriminant;
	double	sqrt_disc;

	if (eq->a == 0)
	{
		if (eq->b != 0)
		{
			eq->t1 = -eq->c / eq->b;
			eq->t2 = eq->t1;
			return (1);
		}
		return (0);
	}
	discriminant = eq->b * eq->b - 4 * eq->a * eq->c;
	if (discriminant < 0)
		return (0);
	sqrt_disc = sqrt(discriminant);
	eq->t1 = (-eq->b - sqrt_disc) / (2 * eq->a);
	eq->t2 = (-eq->b + sqrt_disc) / (2 * eq->a);
	if (discriminant == 0)
		return (1);
	return (2);
}

/*
** Crea un plano a partir de un punto, normal y color
*/
t_plane	plane_from_numbers(t_vector center, t_vector normal, t_color color)
{
	t_plane	plane;

	plane.id = "pl";
	plane.point = center;
	plane.normalized = normal;
	plane.rgb = (t_vector){color.r, color.g, color.b};
	return (plane);
}
