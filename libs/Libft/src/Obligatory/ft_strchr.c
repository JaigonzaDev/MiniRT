/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:12:07 by jaigonza          #+#    #+#             */
/*   Updated: 2024/03/22 12:43:29 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 *	The strchr() function returns a pointer to the first occurrence 
 *	of the character c in the string s.
 */

char	*ft_strchr(const char *s, int c)
{
	unsigned char	d;
	int				i;

	d = c;
	i = 0;
	while ((s[i]) || (i == 0))
	{
		if (s[i] == d)
			return ((char *)&s[i]);
		i++;
	}
	if (d == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
