/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 12:00:00 by jaigonza          #+#    #+#             */
/*   Updated: 2026/04/02 12:00:00 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "render.h"
#include "main.h"

void	ft_put_pixel(t_scene *scene, t_color c, int x, int y)
{
	char	*dst;

	dst = scene->mlx.address + (y * scene->mlx.line_length) \
		+ (x * (scene->mlx.bpp / 8));
	if (scene->mlx.endian == 0)
		*(unsigned int *)dst = (c.t << 24) | (c.r << 16) | (c.g << 8) | c.b;
	else
		*(unsigned int *)dst = (c.t << 24) | (c.b << 16) | (c.g << 8) | c.r;
}
