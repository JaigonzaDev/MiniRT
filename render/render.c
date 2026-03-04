#include "render.h"
#include "../main.h"

/*
** Función wrapper para render
** Llama a la inicialización del viewport y luego al renderizado
*/
int	render(t_scene scene)
{
	ft_init_viewport(&scene);
	return (ft_render(&scene));
}

/*
** Detecta si un rayo intersecta con algún objeto de la escena
** Busca la intersección más cercana iterando sobre todos los objetos
** Retorna: true si hay intersección, false si el rayo no choca con nada
*/
bool	ft_obj_hit(t_scene *scene, t_ray *ray, t_hit *pixel)
{
	bool		hit_anything = false;
	t_sphere	*sp = scene->sphere;
	t_plane		*pl = scene->plane;
	t_cylinder	*cy = scene->cylinder;
	t_hit		temp;
	double		closest_so_far;

	// Obtenemos la distancia inicial desde el pixel de origen (INFINITY general)
	closest_so_far = pixel->t;

	while (sp)
	{
		// Llamamos a hit enviando temp. Si da true y la t_temp < closest
		if (hit_sphere(sp, ray, &temp))
		{
			if (temp.t < closest_so_far)
			{
				hit_anything = true;
				closest_so_far = temp.t;
				*pixel = temp;
			}
		}
		sp = sp->next;
	}
	while (pl)
	{
		if (hit_plane(pl, ray, &temp))
		{
			if (temp.t < closest_so_far)
			{
				hit_anything = true;
				closest_so_far = temp.t;
				*pixel = temp;
			}
		}
		pl = pl->next;
	}
	while (cy)
	{
		if (hit_cylinder(cy, ray, &temp))
		{
			if (temp.t < closest_so_far)
			{
				hit_anything = true;
				closest_so_far = temp.t;
				*pixel = temp;
			}
		}
		cy = cy->next;
	}
	return (hit_anything);
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
	t_hit		pixel;

	coords.y = -1;
	while (++coords.y < HEIGHT)
	{
		coords.x = -1;
		while (++coords.x < WIDTH)
		{
			pixel.color = BLACK;
			pixel.shape = NULL;
			pixel.t = INFINITY;
			factors = ft_canvas_to_viewport((int)coords.x, (int)coords.y);
			ray = ft_cast_ray(scene, factors);
			if (ft_obj_hit(scene, &ray, &pixel))
				ft_illuminate(scene, &pixel);
			ft_put_pixel(scene, pixel.color, (int)coords.x, (int)coords.y);
		}
	}
	mlx_put_image_to_window(scene->mlx.mlx, scene->mlx.mlx_win, 
		scene->mlx.img, 0, 0);
	ft_save_image(scene, "output_new.ppm");
	return (0);
}
