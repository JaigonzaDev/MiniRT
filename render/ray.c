#include "render.h"

/*
** Inicializa el viewport (ventana virtual 3D) de la cámara
** Calcula:
**   - wview/hview: dimensiones del viewport basadas en FOV y aspect ratio
**   - right: vector que apunta a la derecha de la cámara
**   - up: vector que apunta arriba de la cámara
** Estos vectores forman una base ortogonal para proyectar rayos
** Se ejecuta UNA VEZ al inicio para optimizar rendimiento
*/
void	ft_init_viewport(t_scene *scene)
{
	scene->camera.wview = tan(RADIANS(scene->camera.fov / 2.0));
	scene->camera.hview = scene->camera.wview / RATIO;
	scene->camera.right = vector_normal(vector_crossproduct(
		scene->camera.orientation, UPGUIDE));
	scene->camera.up = vector_normal(vector_crossproduct(
		scene->camera.orientation, scene->camera.right));
	scene->camera.right = vector_normal(vector_crossproduct(
		scene->camera.orientation, scene->camera.up));
}
/*
** Convierte coordenadas de pixel (canvas) a factores de viewport
** Pixel coords: (0,0) hasta (WIDTH, HEIGHT)
** Viewport factors: (-1,-1) hasta (1,1)
** Esta normalización permite trabajar independientemente de la resolución
*/t_vector	ft_canvas_to_viewport(int x, int y)
{
	t_vector	converted;
	double		width;
	double		height;

	width = WIDTH;
	height = HEIGHT;
	converted.x = ((2.0 * x) / width) - 1;
	converted.y = ((2.0 * y) / height) - 1;
	converted.z = 0;
	return (converted);
}

/*
** Lanza un rayo desde la cámara hacia un punto del viewport
** Usa los vectores up/right del viewport y los factores para calcular dirección
** Proceso:
**   1. Calcula desplazamiento vertical (up × factor.y × hview)
**   2. Calcula desplazamiento horizontal (right × factor.x × wview)
**   3. Suma vectores para obtener punto en el viewport
**   4. Normaliza dirección del rayo (desde cámara hacia punto)
** Retorna: rayo con origen en la cámara y dirección normalizada
*/
t_ray	ft_cast_ray(t_scene *scene, t_vector factors)
{
	t_ray		ray;
	t_vector	vertical;
	t_vector	horizontal;
	t_vector	res;

	vertical = vector_scale(scene->camera.up, factors.y * scene->camera.hview);
	horizontal = vector_scale(scene->camera.right, 
		factors.x * scene->camera.wview);
	res = vector_add(vertical, horizontal);
	res = vector_add(res, scene->camera.orientation);
	res = vector_add(res, scene->camera.viewpoint);
	ray.origin = scene->camera.viewpoint;
	ray.direction = vector_normal(vector_sub(res, ray.origin));
	return (ray);
}

/*
** Calcula un punto a lo largo del rayo a una distancia 't'
** Ecuación del rayo: P = O + t×D
**   P: punto calculado
**   O: origen del rayo
**   D: dirección del rayo (normalizada)
**   t: distancia desde el origen
** Usado para encontrar el punto exacto de intersección
*/
t_vector	ft_ray_at(t_ray *ray, double t)
{
	return (vector_add(ray->origin, vector_scale(ray->direction, t)));
}
