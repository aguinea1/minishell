/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <aguinea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:07:16 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/16 17:04:14 by aguinea          ###   ########.fr       */
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
