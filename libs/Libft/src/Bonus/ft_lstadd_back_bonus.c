/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:31:25 by jaigonza          #+#    #+#             */
/*   Updated: 2025/07/03 17:11:36 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 *	Add a new node to the end of a linked list.
 */

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*nodo;

	if (lst)
	{
		if (*lst)
		{
			nodo = ft_lstlast(*lst);
			nodo->next = new;
			return ;
		}
		else
		{
			*lst = new;
		}
	}
}
