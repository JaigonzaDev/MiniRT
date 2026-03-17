#include "properties.h"

void skip_space(char **line)
{
    while (**line == ' ' || **line == '\t' || **line == '\n' || **line == '\v' || **line == '\f' || **line == '\r')
        (*line)++;
}

static double read_fraction(char **line)
{
    double result;
    double fraction;

    result = 0.0;
    fraction = 1.0;
    if (**line != '.')
        return (0.0);
    (*line)++;
    while (**line >= '0' && **line <= '9')
    {
        fraction /= 10.0;
        result += (**line - '0') * fraction;
        (*line)++;
    }
    return (result);
}

double get_double(char **line)
{
    double result;
    double sign;

    result = 0.0;
    sign = 1.0;
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
        (*line)++;
    }
    result += read_fraction(line);
    return (result * sign);
}

void insert_data_vector(char **line, t_vector *vector)
{
    vector->x = get_double(line);
    if (**line == ',') (*line)++;
    vector->y = get_double(line);
    if (**line == ',') (*line)++;
    vector->z = get_double(line);
}