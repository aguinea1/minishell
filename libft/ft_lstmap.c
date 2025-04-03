/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:39:02 by arcebria          #+#    #+#             */
/*   Updated: 2025/04/02 17:39:14 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*new;

	if (!lst || !f || !del)
		return (NULL);
	first = NULL;
	while (lst)
	{
		new = ft_lstnew((*f)(lst->content));
		if (!new)
		{
			while (first)
			{
				new = first->next;
				del(first->content);
				free(first);
				first = new;
			}
			lst = NULL;
			return (NULL);
		}
		ft_lstadd_back(&first, new);
		lst = lst->next;
	}
	return (first);
}

/*#include <stdio.h>
#include <string.h>

void    *f(void *content)
{
	char    *str = strdup((char *)content);
	int i;

	i = 0;
	while (str[i])
	{
		str[i] -= 32;
		i++;
	}
	i = 0;
	return((void *)str);
}

void    del(void *content)
{
	free(content);
}

int main(void)
{
	t_list  *head = ft_lstnew(strdup("jkgfdk"));
	t_list  *node1 = ft_lstnew(strdup("djkfgdwkjf"));

	head->next = node1;
	node1->next = NULL;

	t_list  *new_lst = ft_lstmap(head, f, del);

	while (new_lst)
	{
		printf("%s\n", new_lst->content);
		new_lst = new_lst->next;
	}
	return 0;
}*/
