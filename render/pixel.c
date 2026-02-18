#include "render.h"

/*
** Pinta un pixel en la imagen MLX con el color especificado
** Calcula la dirección de memoria exacta del pixel en el buffer de la imagen
** Formato de color: (t << 24 | r << 16 | g << 8 | b)
**   - t: transparencia (no usado)
**   - r: rojo [0-255]
**   - g: verde [0-255]
**   - b: azul [0-255]
*/
void	ft_put_pixel(t_scene *scene, t_color c, int x, int y)
{
	char	*dst;

	// Calcular la dirección de memoria del pixel en el buffer de la imagen
	dst = scene->mlx.address + (y * (int)WIDTH + x) * (scene->mlx.bpp / 8);
	// Establecer el color del pixel en el buffer de la imagen
	*(unsigned int *)dst = (c.t << 24 | c.r << 16 | c.g << 8 | c.b);
}
