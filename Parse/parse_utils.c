#include "properties.h"

void skip_space(char *line)
{
    while (isspace(*line))
        line++;
}

void insert_data_vector(char *line, t_vector *vector)
{
    vector->x = ft_atoi(); 
    skip_space(*line);
    vector->y = ft_atoi();
    skip_space(*line);
    vector->z = ft_atoi();
    skip_space(*line);
}