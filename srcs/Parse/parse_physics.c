/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_physics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 12:12:39 by rlobun            #+#    #+#             */
/*   Updated: 2026/04/08 19:38:58 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	parse_error(const char *msg)
{
	printf("Error\n%s\n", msg);
	exit(1);
}

void	parse_ambient(char **line, t_ambient *scene)
{
	if (scene->id != NULL)
	{
		printf("Error\nAmbient lighting declared more than once\n");
		exit(1);
	}
	scene->id = "A";
	(*line)++;
	skip_space(line);
	scene->light_ratio = get_double(line);
	if (scene->light_ratio < 0.0 || scene->light_ratio > 1.0)
		parse_error("Ambient light ratio must be in [0.0, 1.0]");
	skip_space(line);
	insert_data_vector(line, &scene->rgb);
	validate_line_end(line);
}

void	parse_camera(char **line, t_camera *scene)
{
	if (scene->id != NULL)
	{
		printf("Error\nCamera declared more than once\n");
		exit(1);
	}
	scene->id = "C";
	(*line)++;
	skip_space(line);
	insert_data_vector(line, &scene->viewpoint);
	skip_space(line);
	insert_data_vector(line, &scene->orientation);
	if (vector_length(scene->orientation) <= EPSILON)
		parse_error("Camera orientation vector cannot be zero");
	scene->orientation = vector_normal(scene->orientation);
	skip_space(line);
	scene->fov = get_double(line);
	if (scene->fov <= 0.0 || scene->fov >= 180.0)
		parse_error("Camera FOV must be in (0, 180)");
	validate_line_end(line);
}

void	parse_light(char **line, t_light *scene)
{
	if (scene->id != NULL)
	{
		printf("Error\nLight declared more than once\n");
		exit(1);
	}
	scene->id = "L";
	(*line)++;
	skip_space(line);
	insert_data_vector(line, &scene->light_point);
	skip_space(line);
	scene->brightness = get_double(line);
	if (scene->brightness < 0.0 || scene->brightness > 1.0)
		parse_error("Light brightness must be in [0.0, 1.0]");
	skip_space(line);
	insert_data_vector(line, &scene->rgb);
	validate_line_end(line);
}
