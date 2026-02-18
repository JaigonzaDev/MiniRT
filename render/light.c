#include "render.h"

/*
** Calcula la iluminación total de un punto de intersección
** Combina dos tipos de iluminación:
**   1. Luz ambiental: iluminación base que reciben todos los objetos
**   2. Luz difusa: iluminación direccional desde fuentes de luz (si no está en sombra)
** El color final se almacena en closest->color
*/
void	ft_illuminate(t_scene *scene, t_hit *closest)
{
	t_color	color;

	color = ft_ambient_light(closest->color, scene->ambient.light_ratio);
	if (scene->light.brightness && !ft_is_shadowed(scene, closest))
		color = ft_color_add(color, ft_diffuse_light(&scene->light, closest, 
			scene->light.brightness));
	closest->color = color;
}

/*
** Calcula la componente de luz ambiental
** La luz ambiental ilumina todos los objetos por igual, sin importar orientación
** ratio: intensidad de la luz ambiental [0.0 - 1.0]
** Retorna: color del objeto multiplicado por el ratio ambiental
*/
t_color	ft_ambient_light(t_color color, double ratio)
{
	return (ft_color_mult(color, ratio));
}

/*
** Verifica si un punto está en sombra (bloqueado de la fuente de luz)
** Lanza un "shadow ray" desde el punto de intersección hacia la luz
** Si hay algún objeto en el camino, el punto está en sombra
** TODO: Implementar is_obscured para detección real de oclusión
** Retorna: true si está en sombra, false si recibe luz directa
*/
bool	ft_is_shadowed(t_scene *scene, t_hit *closest)
{
	t_vector	light_dir;
	t_ray		ray;
	double		light_distance;

	light_dir = vector_sub(scene->light.light_point, closest->point);
	light_distance = vector_length(light_dir);
	ray.origin = vector_add(closest->point, VEC_EPSILON);
	ray.direction = vector_normal(light_dir);
	// TODO: Implementar is_obscured - verificar si hay objetos entre el punto y la luz
	return (false);
}

/*
** Calcula la iluminación difusa (modelo de Lambert)
** La intensidad depende de:
**   - Ángulo entre la normal del objeto y la dirección de la luz (cos_angle)
**   - Distancia a la fuente de luz (attenuation)
**   - Intensidad de la luz (brightness)
** Formula: brillo = intensity × cos(ángulo) × atenuación
** Objetos mirando directamente a la luz se ven más brillantes
** Objetos de lado reciben menos luz, objetos de espaldas no reciben luz difusa
*/
t_color	ft_diffuse_light(t_light *light, t_hit *inter, double intensity)
{
	t_vector	light_dir;
	t_color		diff_color;
	double		cos_angle;
	double		diffuse_ratio;
	double		attenuation;

	light_dir = vector_sub(light->light_point, inter->point);
	attenuation = MIN(1.0, 90.0 / vector_length(light_dir));
	cos_angle = vector_dotproduct(vector_normal(inter->normal), 
		vector_normal(light_dir));
	if (cos_angle < 0)
		cos_angle = 0;
	diffuse_ratio = intensity * cos_angle * attenuation;
	diff_color = ft_color_mult(inter->color, diffuse_ratio);
	return (diff_color);
}
