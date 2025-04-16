/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <aguinea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:07:16 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/16 17:04:14 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
#include <stdio.h>
#include <string.h>

void    f(void  *s)
{
	char    *c = (char *)s;

	if (*c >= 'a' && *c <= 'z')
		*c -= 32;
}

int main(void)
{
	t_list  *head = ft_lstnew(strdup("jkgfdk"));
	t_list  *node1 = ft_lstnew(strdup("djkfgdwkjf"));

	head->next = node1;
	node1->next = NULL;
	ft_lstiter(head, f);
	while (head)
	{
		printf("%s\n", head->content);
		head = head->next;
	}
	return 0;
}*/
