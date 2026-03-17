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

static bool	update_hit_if_closer(t_hit *temp, t_hit *pixel, double *closest)
{
	if (temp->t < *closest)
	{
		*closest = temp->t;
		*pixel = *temp;
		return (true);
	}
	return (false);
}

static bool	check_spheres(t_sphere *sp, t_ray *ray, t_hit *pixel, 
			 double *closest)
{
	bool	 hit;
	t_hit	 temp;

	hit = false;
	while (sp)
	{
		if (hit_sphere(sp, ray, &temp))
			hit |= update_hit_if_closer(&temp, pixel, closest);
		sp = sp->next;
	}
	return (hit);
}

static bool	check_planes(t_plane *pl, t_ray *ray, t_hit *pixel, 
			 double *closest)
{
	bool	 hit;
	t_hit	 temp;

	hit = false;
	while (pl)
	{
		if (hit_plane(pl, ray, &temp))
			hit |= update_hit_if_closer(&temp, pixel, closest);
		pl = pl->next;
	}
	return (hit);
}

static bool	check_cylinders(t_cylinder *cy, t_ray *ray, t_hit *pixel, 
			 double *closest)
{
	bool	 hit;
	t_hit	 temp;

	hit = false;
	while (cy)
	{
		if (hit_cylinder(cy, ray, &temp))
			hit |= update_hit_if_closer(&temp, pixel, closest);
		cy = cy->next;
	}
	return (hit);
}

/*
** Detecta si un rayo intersecta con algún objeto de la escena
** Busca la intersección más cercana iterando sobre todos los objetos
** Retorna: true si hay intersección, false si el rayo no choca con nada
*/
bool	ft_obj_hit(t_scene *scene, t_ray *ray, t_hit *pixel)
{
	bool		 hit_anything;
	double		 closest_so_far;

	hit_anything = false;
	closest_so_far = pixel->t;
	hit_anything |= check_spheres(scene->sphere, ray, pixel, &closest_so_far);
	hit_anything |= check_planes(scene->plane, ray, pixel, &closest_so_far);
	hit_anything |= check_cylinders(scene->cylinder, ray, pixel, &closest_so_far);
	return (hit_anything);
}

static void	render_pixel(t_scene *scene, int x, int y)
{
	t_vector	factors;
	t_ray		ray;
	t_hit		pixel;

	pixel.color = BLACK;
	pixel.shape = NULL;
	pixel.t = INFINITY;
	factors = ft_canvas_to_viewport(x, y);
	ray = ft_cast_ray(scene, factors);
	if (ft_obj_hit(scene, &ray, &pixel))
		ft_illuminate(scene, &pixel);
	ft_put_pixel(scene, pixel.color, x, y);
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

	coords.y = -1;
	while (++coords.y < HEIGHT)
	{
		coords.x = -1;
		while (++coords.x < WIDTH)
			render_pixel(scene, (int)coords.x, (int)coords.y);
	}
	mlx_put_image_to_window(scene->mlx.mlx, scene->mlx.mlx_win, 
		scene->mlx.img, 0, 0);
	ft_save_image(scene, "output_new.ppm");
	return (0);
}
