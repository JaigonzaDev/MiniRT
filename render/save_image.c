#include "render.h"
#include "../main.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

/*
** Guarda la imagen renderizada a un archivo PPM
** Formato PPM: Header + datos RGB pixel por pixel
*/
void ft_save_image(t_scene *scene, char *filename)
{
	int fd;
	char header[100];
	int x, y;
	unsigned char rgb[3];
	unsigned int *pixel;
	
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		printf("Error: Could not create file %s\n", filename);
		return;
	}
	
	// Escribir header PPM
	sprintf(header, "P6\n%d %d\n255\n", (int)WIDTH, (int)HEIGHT);
	write(fd, header, strlen(header));
	
	// Escribir pixels
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel = (unsigned int *)(scene->mlx.address + 
				(y * scene->mlx.line_length) + (x * (scene->mlx.bpp / 8)));
			
			// En little-endian, los bytes en memoria están en orden: [B][G][R][T]
			// Para PPM necesitamos escribir en orden: [R][G][B]
			unsigned char *bytes = (unsigned char *)pixel;
			
			if (x == 944 && y == 212 && bytes[2] > 0)
			{
				printf("SAVE x=%d y=%d: bytes=[%d][%d][%d][%d] will write rgb=[%d][%d][%d]\n",
					x, y, bytes[0], bytes[1], bytes[2], bytes[3],
					bytes[2], bytes[1], bytes[0]);
				// Test: write fixed values
				unsigned char test[3] = {99, 55, 11};
				write(fd, test, 3);
				x++;
				continue;
			}
			
			rgb[0] = bytes[2];  // R
			rgb[1] = bytes[1];  // G
			rgb[2] = bytes[0];  // B
			
			write(fd, rgb, 3);
			x++;
		}
		y++;
	}
	
	close(fd);
	printf("Image saved to %s\n", filename);
}
