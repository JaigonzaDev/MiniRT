/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   properties.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 12:13:38 by jaigonza          #+#    #+#             */
/*   Updated: 2026/04/06 21:14:33 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROPERTIES_H
# define PROPERTIES_H

# include <stdbool.h>

# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "get_next_line.h"
# include "vector.h"
# include "objects.h"

typedef struct s_ambient
{
	char		*id;
	double		light_ratio;
	t_vector	rgb;
}	t_ambient;

typedef struct s_camera
{
	char		*id;
	t_vector	viewpoint;
	t_vector	orientation;
	double		fov;
	t_vector	up;
	t_vector	right;
	double		wview;
	double		hview;
}	t_camera;

typedef struct s_light
{
	char		*id;
	t_vector	light_point;
	double		brightness;
	t_vector	rgb;
}	t_light;

struct	s_scene;

void	skip_space(char **line);
bool	get_double(char **line, double *out);
bool	insert_data_vector(char **line, t_vector *vector);
bool	validate_line_end(char **line);

bool	validate_rgb(t_vector color);
bool	validate_normalized_vector(t_vector vec);

bool	parse_ambient(char **line, t_ambient *scene);
bool	parse_camera(char **line, t_camera *scene);
bool	parse_light(char **line, t_light *scene);

bool	parse_sphere(char **line, t_sphere **list);
bool	parse_plane(char **line, t_plane **list);
bool	parse_cylinder(char **line, t_cylinder **list);

bool	parse_properties(char *line, struct s_scene *scene);
void	parse(char **av, struct s_scene *scene);

#endif
