/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlobun <rlobun@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 12:12:29 by rlobun           #+#    #+#             */
/*   Updated: 2026/04/05 17:04:14 by rlobun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "properties.h"

void	skip_space(char **line)
{
	while (**line == ' ' || **line == '\t' || **line == '\n'
		|| **line == '\v' || **line == '\f' || **line == '\r')
		(*line)++;
}

static void	read_fraction(char **line, double *result, int *has_digits)
{
	double	fraction;

	fraction = 1.0;
	if (**line != '.')
		return ;
	(*line)++;
	while (**line >= '0' && **line <= '9')
	{
		fraction /= 10.0;
		*result += (**line - '0') * fraction;
		*has_digits = 1;
		(*line)++;
	}
}

bool	get_double(char **line, double *out)
{
	double	result;
	double	sign;
	int		has_digits;

	result = 0.0;
	sign = 1.0;
	has_digits = 0;
	skip_space(line);
	if (**line == '-' || **line == '+')
	{
		if (**line == '-')
			sign = -1.0;
		(*line)++;
	}
	while (**line >= '0' && **line <= '9')
	{
		result = result * 10.0 + (**line - '0');
		has_digits = 1;
		(*line)++;
	}
	read_fraction(line, &result, &has_digits);
	if (!has_digits)
		return (printf("Error\nInvalid numeric value in scene\n"), false);
	*out = result * sign;
	return (true);
}

bool	insert_data_vector(char **line, t_vector *vector)
{
	if (!get_double(line, &vector->x) || **line != ',')
		return (printf("Error\nInvalid vector format\n"), false);
	(*line)++;
	if (!get_double(line, &vector->y) || **line != ',')
		return (printf("Error\nInvalid vector format\n"), false);
	(*line)++;
	return (get_double(line, &vector->z));
}

bool	validate_line_end(char **line)
{
	skip_space(line);
	if (**line != '\0' && **line != '\n')
		return (printf("Error\nUnexpected trailing chars\n"), false);
	return (true);
}
