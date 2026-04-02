#include "render.h"
#include "main.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

static int	open_ppm(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		printf("Error: Could not create file %s\n", filename);
	return (fd);
}

static void	write_header(int fd)
{
	char	header[100];

	sprintf(header, "P6\n%d %d\n255\n", (int)WIDTH, (int)HEIGHT);
	write(fd, header, strlen(header));
}

static void	write_pixel_row(t_scene *scene, int fd, int y)
{
	int				x;
	unsigned int	*pixel;
	unsigned char	*bytes;
	unsigned char	rgb[3];

	x = 0;
	while (x < WIDTH)
	{
		pixel = (unsigned int *)(scene->mlx.address + \
			(y * scene->mlx.line_length) + (x * (scene->mlx.bpp / 8)));
		if (pixel)
		{
			bytes = (unsigned char *)pixel;
			rgb[0] = bytes[2];
			rgb[1] = bytes[1];
			rgb[2] = bytes[0];
			write(fd, rgb, 3);
		}
		x++;
	}
}

void	ft_save_image(t_scene *scene, char *filename)
{
	int	y;
	int	fd;

	fd = open_ppm(filename);
	if (fd < 0)
		return ;
	write_header(fd);
	y = 0;
	while (y < HEIGHT)
	{
		write_pixel_row(scene, fd, y);
		y++;
	}
	close(fd);
	printf("Image saved to %s\n", filename);
}
