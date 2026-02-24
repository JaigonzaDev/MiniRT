/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:33:08 by jaigonza          #+#    #+#             */
/*   Updated: 2024/10/06 16:07:53 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 * The ft_read() function reads data from a file descriptor 'fd' 
 * into a buffer 'buf' and appends the content to the provided 
 * 'buffer'. It continues reading until a newline character is found 
 * or the end of the file is reached. If a newline is detected, the 
 * function breaks the loop, otherwise it keeps reading.
 */

void	ft_read(int fd, char *buf, char **buffer)
{
	char	*temp;
	int		readbytes;
	size_t	buf_size;

	buf_size = BUFFER_SIZE;
	readbytes = 1;
	if (gnl_strchr(*buffer, '\n'))
		return ;
	while (readbytes > 0)
	{
		readbytes = read(fd, buf, buf_size);
		if (readbytes == -1 || readbytes == 0)
			return ;
		buf[readbytes] = '\0';
		temp = gnl_strjoin(*buffer, buf);
		free(*buffer);
		*buffer = NULL;
		*buffer = temp;
		if (gnl_strchr(buf, '\n'))
			break ;
	}
}

/*
 * The ft_read_text() function allocates memory for a buffer of size 
 * 'BUFFER_SIZE', reads text from a file descriptor 'fd' using 
 * the ft_read() function, and updates the provided 'buffer' with 
 * the new content. If memory allocation fails, it frees the 
 * 'buffer' and returns NULL. If the buffer is empty after reading, 
 * it also frees the buffer and returns NULL.
 */

char	*ft_read_text(int fd, char *buffer)
{
	char	*buf;
	size_t	buf_size;

	buf_size = BUFFER_SIZE;
	buf = (char *)malloc((buf_size + 1) * sizeof(char));
	if (!buf)
	{
		free(buffer);
		return (NULL);
	}
	ft_read(fd, buf, &buffer);
	free(buf);
	if (buffer && buffer[0] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

/*
 * The ft_get_line() function extracts a line from the provided 
 * 'buffer' up to (and including) the newline character, 
 * returning a newly allocated string containing the line. If the 
 * buffer is NULL, it returns NULL. If memory allocation fails, 
 * it frees the original buffer and returns NULL.
 */

char	*ft_get_line(char *buffer)
{
	char	*line;
	int		i;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = (char *)malloc((i + 1) * sizeof(char));
	if (!line)
	{
		free(buffer);
		return (NULL);
	}
	gnl_strlcpy(line, buffer, (i + 1));
	return (line);
}

/*
 * The ft_next_line() function processes the provided 'buffer' to 
 * return the remaining text after the first line (up to the next 
 * newline character). It allocates memory for the remaining text 
 * and updates the original buffer accordingly. If no remaining 
 * text exists, it frees the buffer and returns NULL.
 */

char	*ft_next_line(char **buffer)
{
	int		i;
	char	*rest;

	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	if (!(*buffer)[i])
	{
		free(*buffer);
		*buffer = NULL;
		return (NULL);
	}
	rest = (char *)malloc((gnl_strlen(*buffer) - i + 1) * sizeof(char));
	if (!rest)
	{
		free(*buffer);
		*buffer = NULL;
		return (NULL);
	}
	i++;
	gnl_strlcpy(rest, &((*buffer)[i]), gnl_strlen(*buffer) - i + 1);
	free(*buffer);
	*buffer = rest;
	return (*buffer);
}

/*
 * The get_next_line() function retrieves the next line from a 
 * specified file descriptor 'fd'. It manages memory for the static 
 * buffer, initializes it if necessary, and uses other functions to 
 * read text, extract a line, and update the buffer. It returns the 
 * next line as a string or NULL if there are no more lines or an 
 * error occurs.
 */

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = initialize_buffer(buffer);
	if (!buffer)
		return (NULL);
	buffer = ft_read_text(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_get_line(buffer);
	if (!line)
	{
		buffer = NULL;
		return (NULL);
	}
	buffer = ft_next_line(&buffer);
	return (line);
}