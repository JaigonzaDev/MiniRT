/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:10:39 by jaigonza          #+#    #+#             */
/*   Updated: 2025/07/03 17:07:48 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 *	The malloc() function allocates size bytes and 
 *	returns a pointer to the allocated memory.
 */

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	p = (void *)malloc(count * size);
	if (p != NULL)
	{
		p = ft_memset(p, 0, count * size);
		return (p);
	}
	return (NULL);
}
