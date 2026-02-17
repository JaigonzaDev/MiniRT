struct typedef s_ambient
{
    char *id;
    int light_ratio;
    int *rgb;
} t_ambient;

struct typedef s_camera
{
    char *id;
    t_vector *viewpoint;
    t_vector *orentation;
    int fov;
} t_camera;

struct typedef s_light
{
    char *id;
    t_vector light_point;
    int *brightness;
    int *rgb;
} t_light;

struct typedef s_properties
{
    int ambient_light;
    int camara;
    int light;
    int plane;
    int sphere;
    int cylinder;
} t_properties;

t_properties parse_properties (char **av) 
{
    t_properties properties;

    if (av == NULL || *av == NULL)
        return (NULL);
    while (*av != NULL) 
    {
        if (**av == 'A')
            data_ambient();
        else if (**av == 'C')
            data_camera();
        else if (**av == 'L')
            data_light();
        else
            ft_printf("Error: Properties not well defined\n");
    }
    return (properties);
}