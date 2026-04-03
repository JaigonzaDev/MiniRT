#include "properties.h"

void	parse_error(char *message)
{
	printf("Error\n%s\n", message);
	exit(1);
}

void	skip_space(char **line)
{
	while (**line == ' ' || **line == '\t' || **line == '\n'
		|| **line == '\v' || **line == '\f' || **line == '\r')
		(*line)++;
}

double	get_double(char **line)
{
	double	result;
	double	sign;
	double	fraction;
	int		has_digits;

	result = 0.0;
	sign = 1.0;
	fraction = 1.0;
	has_digits = 0;
	skip_space(line);
	if (**line == '-')
	{
		sign = -1.0;
		(*line)++;
	}
	else if (**line == '+')
		(*line)++;
	while (**line >= '0' && **line <= '9')
	{
		result = result * 10.0 + (**line - '0');
		has_digits = 1;
		(*line)++;
	}
	if (**line == '.')
	{
		(*line)++;
		while (**line >= '0' && **line <= '9')
		{
			fraction /= 10.0;
			result += (**line - '0') * fraction;
			has_digits = 1;
			(*line)++;
		}
	}
	if (!has_digits)
		parse_error("Invalid numeric value in scene file");
	return (result * sign);
}

void	insert_data_vector(char **line, t_vector *vector)
{
	vector->x = get_double(line);
	if (**line != ',')
		parse_error("Invalid vector format, expected comma-separated values");
	(*line)++;
	vector->y = get_double(line);
	if (**line != ',')
		parse_error("Invalid vector format, expected comma-separated values");
	(*line)++;
	vector->z = get_double(line);
}

void	validate_line_end(char **line)
{
	skip_space(line);
	if (**line != '\0' && **line != '\n')
		parse_error("Unexpected trailing characters in scene line");
}
