/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:36:30 by arcebria          #+#    #+#             */
/*   Updated: 2025/04/02 17:41:13 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

/*
#include <stdio.h>
int main(void)
{
	t_list  *node = ft_lstnew("A");
	t_list  *node2 = ft_lstnew("B");
	t_list  *node3 = ft_lstnew("C");

	node->next = node2;
	node2->next = node3;
	node3->next = NULL;
	printf("El numero de nodos en la lista es: %d\n", ft_lstsize(node));
	free(node);
	free(node2);
	free(node3);
	return (0);
}*/
