#include "main.h"

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
	skip_space(line);
	scene->fov = get_double(line);
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
	skip_space(line);
	insert_data_vector(line, &scene->rgb);
	validate_line_end(line);
}
