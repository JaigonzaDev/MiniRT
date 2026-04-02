#include "render.h"

/*
** Limita un valor entero entre un mínimo y un máximo
** Utilizado para asegurar que los valores RGB estén en el rango [0, 255]
*/
int	ft_clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

/*
** Crea una estructura de color RGB
** Aplica clamp automáticamente a cada componente para evitar overflow
** Retorna: estructura t_color con valores RGB válidos [0-255]
*/
t_color	ft_color_create(int r, int g, int b)
{
	t_color	color;

	color.t = 0;
	color.r = ft_clamp(r, 0, 255);
	color.g = ft_clamp(g, 0, 255);
	color.b = ft_clamp(b, 0, 255);
	return (color);
}

/*
** Suma dos colores componente por componente (R+R, G+G, B+B)
** Aplica clamp para evitar que la suma supere 255
** Usado para combinar iluminación ambiental y difusa
*/
t_color	ft_color_add(t_color c1, t_color c2)
{
	t_color	color;

	color.t = 0;
	color.r = ft_clamp(c1.r + c2.r, 0, 255);
	color.g = ft_clamp(c1.g + c2.g, 0, 255);
	color.b = ft_clamp(c1.b + c2.b, 0, 255);
	return (color);
}

/*
** Multiplica un color por un escalar (factor de intensidad)
** k: factor multiplicador (0.0 = negro, 1.0 = color original, >1.0 = más brillante)
** Usado para aplicar ratios de iluminación (ambiental, difusa, atenuación)
*/
t_color	ft_color_mult(t_color color, double k)
{
	t_color	result;

	result.t = 0;
	result.r = ft_clamp((int)(color.r * k), 0, 255);
	result.g = ft_clamp((int)(color.g * k), 0, 255);
	result.b = ft_clamp((int)(color.b * k), 0, 255);
	return (result);
}
