#include "render.h"
#include "../main.h"

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
	static int debug = 0;

	// Calcular la dirección de memoria del pixel en el buffer de la imagen
	dst = scene->mlx.address + (y * scene->mlx.line_length) + (x * (scene->mlx.bpp / 8));
	// En little-endian (endian=0), el orden en memoria es: B G R A
	if (scene->mlx.endian == 0)
		*(unsigned int *)dst = (c.t << 24) | (c.r << 16) | (c.g << 8) | c.b;
	else
		*(unsigned int *)dst = (c.t << 24) |  (c.b << 16) | (c.g << 8) | c.r;
	
	if (debug < 3 && (c.r > 0 || c.g > 0 || c.b > 0))
	{
		unsigned int val = *(unsigned int *)dst;
		printf("Pixel (%d,%d): input RGB=(%d,%d,%d) → written=0x%08X → bytes=[%d][%d][%d][%d]\n",
			x, y, c.r, c.g, c.b, val,
			((unsigned char *)dst)[0], ((unsigned char *)dst)[1],
			((unsigned char *)dst)[2], ((unsigned char *)dst)[3]);
		debug++;
	}
}
