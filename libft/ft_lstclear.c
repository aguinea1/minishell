/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:37:57 by arcebria          #+#    #+#             */
/*   Updated: 2025/04/02 17:47:32 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!*lst || !lst || del)
		return ;
	while (*lst && lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
}
/*
#include <stdio.h>

void    del(void *content)
{
	free(content);
}

int main(void)
{
	t_list  *head = ft_lstnew("jsxs");
	t_list  *node1 = ft_lstnew("djlfd");

	head->next = node1;
	node1->next = NULL;
	while (head)
	{
		printf("%s\n", head->content);
		head = head->next;
	}
	ft_lstclear(&head, del);
	if (head == NULL)
		printf("Lista eliminada con exito");
	return 0;
}*/
