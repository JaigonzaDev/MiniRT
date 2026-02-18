#include "render.h"

/*
** Detecta si un rayo intersecta con algún objeto de la escena
** Busca la intersección más cercana iterando sobre todos los objetos
** TODO: Implementar intersecciones con sphere, plane, cylinder
** Retorna: true si hay intersección, false si el rayo no choca con nada
*/
bool	ft_obj_hit(t_scene *scene, t_ray *ray, t_hit *closest)
{
	// TODO: Implementar intersecciones con sphere, plane, cylinder
	// Por ahora retorna false - no hay intersecciones
	(void)scene;
	(void)ray;
	(void)closest;
	return (false);
}

/*
** Función principal de renderizado - corazón del ray tracer
** Itera sobre cada pixel de la pantalla (WIDTH x HEIGHT)
** Para cada pixel:
**   1. Convierte coordenadas de canvas a viewport
**   2. Lanza un rayo desde la cámara
**   3. Busca intersecciones con objetos
**   4. Calcula iluminación si hay intersección
**   5. Pinta el pixel con el color calculado
** Finalmente muestra la imagen completa en la ventana MLX
*/
int	ft_render(t_scene *scene)
{
	t_vector	coords;
	t_vector	factors;
	t_ray		ray;
	t_hit		closest;

	coords.y = -1;
	while (++coords.y < HEIGHT)
	{
		coords.x = -1;
		while (++coords.x < WIDTH)
		{
			closest.color = BLACK;
			closest.shape = NULL;
			closest.t = INFINITY;
			factors = ft_canvas_to_viewport((int)coords.x, (int)coords.y);
			ray = ft_cast_ray(scene, factors);
			if (ft_obj_hit(scene, &ray, &closest))
				ft_illuminate(scene, &closest);
			ft_put_pixel(scene, closest.color, (int)coords.x, (int)coords.y);
		}
	}
	mlx_put_image_to_window(scene->mlx.mlx, scene->mlx.mlx_win, 
		scene->mlx.img, 0, 0);
	return (0);
}
