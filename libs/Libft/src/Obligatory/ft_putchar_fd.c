/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:43:42 by jaigonza          #+#    #+#             */
/*   Updated: 2025/07/03 17:08:39 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 *	Writes a character (c) to a specified file descriptor (fd). 
 */

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
