/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:39:54 by jaigonza          #+#    #+#             */
/*   Updated: 2024/04/17 16:56:03 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 *	The itoa() function constructs a string representation of an integer.
 */

char	*fill(char const *s1, char const *s2, char *str)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	z;

	i = 0;
	j = 0;
	z = 0;
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	i = 0;
	while (s1[i])
	{
		str[z] = s1[i];
		z++;
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[z] = s2[j];
		z++;
		j++;
	}
	str[z] = '\0';
	return (str);
}
/*
 *	Concatenates two strings (s1 and s2) into a new string.
 */

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	str = (char *)malloc((i + j + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str = fill(s1, s2, str);
	return (str);
}
