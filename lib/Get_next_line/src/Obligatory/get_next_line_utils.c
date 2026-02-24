/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:33:08 by jaigonza          #+#    #+#             */
/*   Updated: 2024/10/06 16:07:53 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 * The gnl_strlen() function calculates the length of the string 
 * pointed to by 'str', excluding the null terminator. It iterates 
 * through the characters of the string until it encounters the 
 * null terminator, returning the total number of characters.
 */

size_t	gnl_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

/*
 * The gnl_strjoin() function concatenates two strings pointed to by 
 * 's1' and 's2', allocating sufficient memory for the new string 
 * which includes both original strings and a null terminator. It 
 * copies the content of 's1' followed by 's2' into the new memory 
 * area and returns a pointer to the new string.
 */
char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	size_t	i;
	size_t	j;

	if (s1 && s2)
	{
		new_s = (char *)malloc((gnl_strlen(s1) + gnl_strlen(s2) + 1) * 1);
		if (new_s == NULL)
			return (NULL);
		i = 0;
		j = 0;
		while (s1[i])
			new_s[j++] = s1[i++];
		j = 0;
		while (s2[j])
			new_s[i++] = s2[j++];
		new_s[i] = '\0';
		return (new_s);
	}
	return (NULL);
}

/*
 * The gnl_strchr() function searches for the first occurrence of 
 * the character 'c' in the string pointed to by 's'. It returns 
 * 1 if the character is found and 0 if it is not. This function 
 * is useful for checking the presence of a specific character 
 * within a string.
 */

int	gnl_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		++i;
	}
	return (0);
}

/*
 * The ft_strlcpy() function copies up to 'dstsize - 1' characters 
 * from the string pointed to by 'src' to the buffer pointed to by 
 * 'dst', ensuring that 'dst' is null-terminated. It returns the 
 * total length of the source string. This function is safer than 
 * 'strcpy' as it prevents buffer overflows.
 */

size_t	gnl_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (src[len])
		len++;
	if (dstsize > 0)
	{
		while (i < (dstsize - 1) && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len);
}

/*
 * The initialize_buffer() function allocates memory for a buffer 
 * if the pointer 'buffer' is NULL. It initializes the first element 
 * to the null terminator, effectively creating an empty string. 
 * If memory allocation fails, it returns NULL.
 */

char	*initialize_buffer(char *buffer)
{
	if (!buffer)
	{
		buffer = (char *)malloc(sizeof(char));
		if (!buffer)
			return (NULL);
		buffer[0] = '\0';
	}
	return (buffer);
}
