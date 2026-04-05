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

double	get_double(char **line)
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
		(printf("Error\nInvalid numeric value in scene file\n"), exit(1));
	return (result * sign);
}

void	insert_data_vector(char **line, t_vector *vector)
{
	vector->x = get_double(line);
	if (**line != ',')
	{
		printf("Error\nInvalid vector format\n");
		exit(1);
	}
	(*line)++;
	vector->y = get_double(line);
	if (**line != ',')
	{
		printf("Error\nInvalid vector format\n");
		exit(1);
	}
	(*line)++;
	vector->z = get_double(line);
}

void	validate_line_end(char **line)
{
	skip_space(line);
	if (**line != '\0' && **line != '\n')
	{
		printf("Error\nUnexpected trailing characters in scene line\n");
		exit(1);
	}
}
