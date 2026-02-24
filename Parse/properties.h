#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_next_line.h"
#include "../vector/vector.h"
#include "../objects/objects.h"

typedef struct s_ambient
{
    char *id;
    double light_ratio;
    t_vector rgb;
} t_ambient;

typedef struct s_camera
{
    char *id;
    t_vector viewpoint;
    t_vector orientation;
    double fov;
    // Campos adicionales para viewport
    t_vector up;
    t_vector right;
    double wview;
    double hview;
} t_camera;

typedef struct s_light
{
    char *id;
    t_vector light_point;
    double brightness;
    t_vector rgb;
} t_light;

struct s_scene;

void skip_space(char **line);
double get_double(char **line);
void insert_data_vector(char **line, t_vector *vector);

void parse_ambient(char **line, t_ambient *scene);
void parse_camera(char **line, t_camera *scene);
void parse_light(char **line, t_light *scene);

void parse_sphere(char **line, t_sphere *scene);
void parse_plane(char **line, t_plane *scene);
void parse_cylinder(char **line, t_cylinder *scene);

void parse_properties(char *line, struct s_scene *scene);
void parse(char **av, struct s_scene *scene);

#endif