/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:25:40 by jaigonza          #+#    #+#             */
/*   Updated: 2025/07/03 17:11:00 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 *	The strlen() function calculates the length of the string s.
 */

size_t	ft_strlen(const char *s)
{
	const char	*p;
	size_t		i;

	p = s;
	i = 0;
	while (*p != '\0')
	{
		i++;
		p++;
	}
	return (i);
}
