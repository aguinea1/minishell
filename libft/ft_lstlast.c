/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:38:52 by arcebria          #+#    #+#             */
/*   Updated: 2025/04/02 17:38:59 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}
/*
#include <stdio.h>
int main(void)
{
	t_list  *node = ft_lstnew("hola");
	t_list  *node2 = ft_lstnew("adios");

	node->next = node2;
	node2->next = NULL;
	printf("%s\n", (char *)ft_lstlast(node)->content);
	return (0);
}*/
