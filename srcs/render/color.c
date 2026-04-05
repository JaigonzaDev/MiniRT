/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 12:12:26 by jaigonza          #+#    #+#             */
/*   Updated: 2026/04/05 12:14:12 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	ft_clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

t_color	ft_color_create(int r, int g, int b)
{
	t_color	color;

	color.t = 0;
	color.r = ft_clamp(r, 0, 255);
	color.g = ft_clamp(g, 0, 255);
	color.b = ft_clamp(b, 0, 255);
	return (color);
}

t_color	ft_color_add(t_color c1, t_color c2)
{
	t_color	color;

	color.t = 0;
	color.r = ft_clamp(c1.r + c2.r, 0, 255);
	color.g = ft_clamp(c1.g + c2.g, 0, 255);
	color.b = ft_clamp(c1.b + c2.b, 0, 255);
	return (color);
}

t_color	ft_color_mult(t_color color, double k)
{
	t_color	result;

	result.t = 0;
	result.r = ft_clamp((int)(color.r * k), 0, 255);
	result.g = ft_clamp((int)(color.g * k), 0, 255);
	result.b = ft_clamp((int)(color.b * k), 0, 255);
	return (result);
}
