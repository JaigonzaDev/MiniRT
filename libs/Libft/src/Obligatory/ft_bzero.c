/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:30:13 by jaigonza          #+#    #+#             */
/*   Updated: 2025/07/03 17:09:49 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 *	The bzero() function sets the first 
 *	n bytes of the area starting at s to zero.
 */

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	if (n > 0)
	{
		while (n-- > 0)
			*ptr++ = 0;
		return ;
	}
	else
	{
		return ;
	}
}
