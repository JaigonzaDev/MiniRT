/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:44:56 by jaigonza          #+#    #+#             */
/*   Updated: 2025/07/03 17:09:07 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 *	Searches for the last occurrence of 
 *	a specific character c in a string s.
 */

char	*ft_strrchr(const char *s, int c)
{
	char	d;
	int		i;

	d = c;
	i = ft_strlen(s);
	while (i > 0)
	{
		if (s[i] == d)
			return ((char *)s + i);
		i--;
	}
	if (s[i] == d)
		return ((char *)s + i);
	return (NULL);
}
