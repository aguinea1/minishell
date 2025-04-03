/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:35:59 by arcebria          #+#    #+#             */
/*   Updated: 2025/04/02 17:40:30 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*head;

	head = malloc(sizeof(t_list));
	if (!head)
		return (NULL);
	head->content = content;
	head->next = NULL;
	return (head);
}

/*
#include <stdio.h>
int main(void)
{
	int x = 42;
	t_list *new_node = ft_lstnew(&x);
	if (new_node)
	{
		printf("El : %d\n", *(int *)new_node->content);
		free(new_node);
	}
	else
		printf("Error");
	return(0);
}*/
